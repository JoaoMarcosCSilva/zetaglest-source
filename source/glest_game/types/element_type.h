// ==============================================================
//      This file is part of Glest (www.glest.org)
//
//      Copyright (C) 2001-2008 Martiño Figueroa
//
//      You can redistribute this code and/or modify it under 
//      the terms of the GNU General Public License as published 
//      by the Free Software Foundation; either version 2 of the 
//      License, or (at your option) any later version
// ==============================================================

#ifndef _GLEST_GAME_ELEMENTTYPE_H_
#   define _GLEST_GAME_ELEMENTTYPE_H_

#   ifdef WIN32
#      include <winsock2.h>
#      include <winsock.h>
#   endif

#   include <vector>
#   include <string>
#   include "texture.h"
#   include "resource.h"
#   include "leak_dumper.h"

using std::vector;
using std::string;

using Shared::Graphics::Texture2D;

namespace Glest {
	namespace Game {

		class UpgradeType;
		class TechTree;
		class UnitType;
		class UpgradeType;
		class DisplayableType;
		class ResourceType;

		// =====================================================
		//      class DisplayableType
		//
		///     Base class for anything that has a name and a portrait
		// =====================================================

		class DisplayableType {
		protected:
			string name;              //name
			Texture2D *image;         //portrait  

		public:
			DisplayableType();
			virtual ~DisplayableType() {
			};

			//get
			virtual string getName(bool translatedValue = false) const;
			virtual const Texture2D *getImage() const {
				return image;
			}

			//virtual void saveGame(XmlNode *rootNode) const;
		};


		// =====================================================
		//      class RequirableType  
		//
		///     Base class for anything that has requirements
		// =====================================================

		class RequirableType :public DisplayableType {
		private:
			typedef vector < const UnitType *>UnitReqs;
			typedef vector < const UpgradeType *>UpgradeReqs;
			typedef vector < Resource > Costs;

		protected:
			UnitReqs unitReqs;        //needed units
			UpgradeReqs upgradeReqs;  //needed upgrades
			Costs costs;              //needed costs

		public:
			//get
			int getUpgradeReqCount() const {
				return (int) upgradeReqs.size();
			}
			int getUnitReqCount() const {
				return (int) unitReqs.size();
			}
			const UpgradeType *getUpgradeReq(int i) const {
				return upgradeReqs[i];
			}
			const UnitType *getUnitReq(int i) const {
				return unitReqs[i];
			}
			//get
			int getCostCount() const {
				return (int) costs.size();
			}
			const Resource *getCost(int i) const {
				return &costs[i];
			}
			const Resource *getCost(const ResourceType * rt) const;

			//other
			virtual string getReqDesc(bool translatedValue) const;

			string getResourceReqDesc(bool lineBreaks, bool translatedValue) const;
			string getUnitAndUpgradeReqDesc(bool lineBreaks,
				bool translatedValue) const;
			string getReqDesc(bool ignoreResourceRequirements,
				bool translatedValue) const;

			//virtual void saveGame(XmlNode *rootNode) const;
		};


		// =====================================================
		//      class ProducibleType  
		//
		///     Base class for anything that can be produced
		// =====================================================

		class ProducibleType :public RequirableType {
		protected:
			Texture2D *cancelImage;
			int productionTime;

		public:
			ProducibleType();
			virtual ~ProducibleType();

			int getProductionTime() const {
				return productionTime;
			}
			const Texture2D *getCancelImage() const {
				return cancelImage;
			}

			//      virtual void saveGame(XmlNode *rootNode) const;
			//      void loadGame(const XmlNode *rootNode);
		};

	}
}                              //end namespace

#endif
