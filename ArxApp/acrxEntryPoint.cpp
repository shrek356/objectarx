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


	static void SbsArxapp() {
		ads_name ss;
		int rt = acedSSGet(nullptr, nullptr, nullptr,nullptr, ss);
		AcDbObjectIdArray object_ids;
		if(rt==RTNORM)
		{
			Adesk::Int32 length;
			acedSSLength(ss, &length);
			for(int i=0;i<length;i++)
			{
				ads_name ent;
				acedSSName(ss, i, ent);
				AcDbObjectId obj_id;
				acdbGetObjectId(obj_id, ent);
				object_ids.append(obj_id);

			}
			
		}
		acedSSFree(ss);
		CHatchUtil::Add(object_ids,L"BRICK",25);



	}

};

//-----------------------------------------------------------------------------a
IMPLEMENT_ARX_ENTRYPOINT(CArxAppApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CArxAppApp, Sbs, Arxapp, ASW, ACRX_CMD_MODAL, NULL)

