// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("Sbs")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CArxAppApp : public AcRxArxApp {

public:
	CArxAppApp() : AcRxArxApp() {}
	virtual ~CArxAppApp() {	};

	AcRx::AppRetCode On_kInitAppMsg(void* pkt) override {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);

		// TODO: Add your initialization code here

		return (retCode);
	}

	AcRx::AppRetCode On_kUnloadAppMsg(void* pkt) override {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);

		// TODO: Unload dependencies here

		return (retCode);
	}

	void RegisterServerComponents() override {

	}


	static void SbsArxapp()
	{
		//auto line_id=CLineUtil::Add(AcGePoint3d::kOrigin, AcGePoint3d(1000, 1000, 0));

		auto ids = CDwgDatabaseUtil::GetEntityId();



		AcArray<AcDbLine*> p_lines = { 0 };
		AcArray<AcDbBlockReference*> p_refs{ 0 };
		for(const auto e:ids)
		{
			AcDbEntity* p_ent = nullptr;
			acdbOpenObject(p_ent, e, AcDb::kForRead);
			if(p_ent->isKindOf(AcDbLine::desc()))
			{
				p_lines.append(static_cast<AcDbLine*>(p_ent));
			}
			else if(p_ent->isKindOf(AcDbBlockReference::desc()))
			{
				p_refs.append(static_cast<AcDbBlockReference*>(p_ent));
			}
			else
			{
				acutPrintf(L"not a type of ref and line");
			}
			p_ent->close();
		}

		for(const auto ref:p_refs)
		{
			AcGePoint3dArray intersected_pts;
			for(const auto line:p_lines)
			{
				CBlockUtil::CheckIntersectionBetweenBlockAndEntity(ref, line, intersected_pts,false);
			}
			for(auto center_point :intersected_pts)
			{
				auto e_id=CCircleUtil::Add(center_point, 5);
				CEntityUtil::SetColor(e_id, 4);
			}
		}

		


	}

};

//-----------------------------------------------------------------------------a
IMPLEMENT_ARX_ENTRYPOINT(CArxAppApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CArxAppApp, Sbs, Arxapp, ASW, ACRX_CMD_MODAL, NULL)

