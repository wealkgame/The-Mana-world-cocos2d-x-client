/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCTMXTiledMap.h"
#include "CCTMXXMLParser.h"
#include "CCTMXLayer.h"
#include "CCSprite.h"
#include "CGPointExtension.h"

namespace cocos2d{

	// implementation CCTMXTiledMap
	CCTMXTiledMap * CCTMXTiledMap::tiledMapWithTMXFile(const char *tmxFile)
	{
		CCTMXTiledMap *pRet = new CCTMXTiledMap();
		if (pRet->initWithTMXFile(tmxFile))
		{
			pRet->autorelease();
			return pRet;
		}
        CCX_SAFE_DELETE(pRet);
		return NULL;
	}
	bool CCTMXTiledMap::initWithTMXFile(const char *tmxFile)
	{
		NSAssert(tmxFile != NULL && strlen(tmxFile)>0, "TMXTiledMap: tmx file should not bi nil");
		
		setContentSize(CGSizeZero);

		CCTMXMapInfo *mapInfo = CCTMXMapInfo::formatWithTMXFile(tmxFile);
    
        if (! mapInfo)
        {
            return false;
        }
		NSAssert( mapInfo->getTilesets()->count() != 0, "TMXTiledMap: Map not found. Please check the filename.");

		m_tMapSize = mapInfo->getMapSize();
		m_tTileSize = mapInfo->getTileSize();
		m_nMapOrientation = mapInfo->getOrientation();
		setObjectGroups(mapInfo->getObjectGroups());
		setProperties(mapInfo->getProperties());
		CCX_SAFE_RELEASE(m_pTileProperties);
		m_pTileProperties = mapInfo->getTileProperties();
		CCX_SAFE_RETAIN(m_pTileProperties);

		int idx = 0;

		NSMutableArray<CCTMXLayerInfo*>* layers = mapInfo->getLayers();
		if (layers && layers->count()>0)
		{
			CCTMXLayerInfo *layerInfo = NULL;
			NSMutableArray<CCTMXLayerInfo*>::NSMutableArrayIterator it;
			for (it = layers->begin(); it != layers->end(); ++it)
			{
				layerInfo = *it;
				if (layerInfo && layerInfo->m_bVisible)
				{
					CCTMXLayer *child = parseLayer(layerInfo, mapInfo);
					addChild((CCNode*)child, idx, idx);

					// update content size with the max size
					CGSize childSize = child->getContentSize();
					CGSize currentSize = this->getContentSize();
					currentSize.width = MAX( currentSize.width, childSize.width );
					currentSize.height = MAX( currentSize.height, childSize.height );
					this->setContentSize(currentSize);

					idx++;
				}
			}
		}
		return true;
	}
	CCTMXTiledMap::CCTMXTiledMap()
		:m_tTileSize(CGSizeZero)
		,m_tMapSize(CGSizeZero)
		,m_pObjectGroups(NULL)
		,m_pProperties(NULL)
		,m_pTileProperties(NULL)
	{
	}
	CCTMXTiledMap::~CCTMXTiledMap()
	{
		CCX_SAFE_RELEASE(m_pProperties);
		CCX_SAFE_RELEASE(m_pObjectGroups);
		CCX_SAFE_RELEASE(m_pTileProperties);
	}
	NSMutableArray<CCTMXObjectGroup*> * CCTMXTiledMap::getObjectGroups()
	{
		return m_pObjectGroups;
	}
	void CCTMXTiledMap::setObjectGroups(NSMutableArray<CCTMXObjectGroup*>* var)
	{
		CCX_SAFE_RETAIN(var);
		CCX_SAFE_RELEASE(m_pObjectGroups);
		m_pObjectGroups = var;
	}
	CCXStringToStringDictionary * CCTMXTiledMap::getProperties()
	{
		return m_pProperties;
	}
	void CCTMXTiledMap::setProperties(CCXStringToStringDictionary* var)
	{
		CCX_SAFE_RETAIN(var);
		CCX_SAFE_RELEASE(m_pProperties);
		m_pProperties = var;
	}
	// private
	CCTMXLayer * CCTMXTiledMap::parseLayer(CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo)
	{
		CCTMXTilesetInfo *tileset = tilesetForLayer(layerInfo, mapInfo);
		CCTMXLayer *layer = CCTMXLayer::layerWithTilesetInfo(tileset, layerInfo, mapInfo);

		// tell the layerinfo to release the ownership of the tiles map.
		layerInfo->m_bOwnTiles = false;
		layer->setupTiles();

		return layer;
	}
	
	CCTMXTilesetInfo * CCTMXTiledMap::tilesetForLayer(CCTMXLayerInfo *layerInfo, CCTMXMapInfo *mapInfo)
	{
		CCTMXTilesetInfo *tileset = NULL;
		//CFByteOrder o = CFByteOrderGetCurrent();

		CGSize size = layerInfo->m_tLayerSize;
		NSMutableArray<CCTMXTilesetInfo*>* tilesets = mapInfo->getTilesets();
		if (tilesets && tilesets->count()>0)
		{
			CCTMXTilesetInfo *tileset = NULL;
			NSMutableArray<CCTMXTilesetInfo*>::NSMutableArrayRevIterator rit;
			for (rit = tilesets->rbegin(); rit != tilesets->rend(); ++rit)
			{
				tileset = *rit;
				if (tileset)
				{
					for( unsigned int y=0; y < size.height; y++ )
					{
						for( unsigned int x=0; x < size.width; x++ ) 
						{
							unsigned int pos = (unsigned int)(x + size.width * y);
							unsigned int gid = layerInfo->m_pTiles[ pos ];

							// gid are stored in little endian.
							// if host is big endian, then swap
							//if( o == CFByteOrderBigEndian )
							//	gid = CFSwapInt32( gid );
							/* We support little endian.*/

							// XXX: gid == 0 --> empty tile
							if( gid != 0 ) 
							{
								// Optimization: quick return
								// if the layer is invalid (more than 1 tileset per layer) an assert will be thrown later
								if( gid >= tileset->m_uFirstGid )
									return tileset;
							}
						}
					}		
				}
			}
		}

		// If all the tiles are 0, return empty tileset
		CCLOG("cocos2d: Warning: TMX Layer '%@' has no tiles", layerInfo->m_sName);
		return tileset;
	}


	// public
	CCTMXLayer * CCTMXTiledMap::layerNamed(const char *layerName)
	{
		std::string sLayerName = layerName;
		if (m_pChildren && m_pChildren->count()>0)
		{
			CCTMXLayer *layer;
			NSMutableArray<CCNode*>::NSMutableArrayIterator it;
			for (it = m_pChildren->begin(); it != m_pChildren->end(); ++it)
			{
				layer = (CCTMXLayer*)(*it);
				if (layer && layer->getLayerName() == sLayerName)
				{
					return layer;
				}
			}
		}
		
		// layer not found
		return NULL;
	}
	CCTMXObjectGroup * CCTMXTiledMap::objectGroupNamed(const char *groupName)
	{
		std::string sGroupName = groupName;
		if (m_pObjectGroups && m_pObjectGroups->count()>0)
		{
			CCTMXObjectGroup *objectGroup;
			NSMutableArray<CCTMXObjectGroup*>::NSMutableArrayIterator it;
			for (it = m_pObjectGroups->begin(); it != m_pObjectGroups->end(); ++it)
			{
				objectGroup = (CCTMXObjectGroup*)(*it);
				if (objectGroup && objectGroup->getGroupName() == sGroupName)
				{
					return objectGroup;
				}
			}
		}

		// objectGroup not found
		return NULL;
	}

	// XXX deprecated
	CCTMXObjectGroup * CCTMXTiledMap::groupNamed(const char *groupName)
	{
		return objectGroupNamed(groupName);
	}
	NSString * CCTMXTiledMap::propertyNamed(const char *propertyName)
	{
		return m_pProperties->objectForKey(std::string(propertyName));
	}
	NSDictionary<std::string, NSString*> * CCTMXTiledMap::propertiesForGID(int GID)
	{
		return m_pTileProperties->objectForKey(GID);
	}
		

}// namespace cocos2d

