//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "TessendorfOcean.h"

#define TessendorfOcean_CLASS_ID	Class_ID(0x6e25d3e5, 0xa605dbad)

#define PBLOCK_REF	0

class TessendorfOcean : public SimpleObject2
{
public:
	//Constructor/Destructor
	TessendorfOcean();
	virtual ~TessendorfOcean();

	// Parameter block handled by parent

	// From BaseObject
	virtual CreateMouseCallBack* GetCreateMouseCallBack();

	// From Object
	virtual BOOL HasUVW();
	virtual void SetGenUVW(BOOL sw);
	virtual int CanConvertToType(Class_ID obtype);
	virtual Object* ConvertToType(TimeValue t, Class_ID obtype);
	virtual void GetCollapseTypes(Tab<Class_ID>& clist,Tab<TSTR*>& nlist);
	virtual int IntersectRay(TimeValue t, Ray& ray, float& at, Point3& norm);

	// From Animatable
	virtual void BeginEditParams( IObjParam  *ip, ULONG flags,Animatable *prev);
	virtual void EndEditParams( IObjParam *ip, ULONG flags,Animatable *next);

	// From SimpleObject
	virtual void BuildMesh(TimeValue t);
	virtual void InvalidateUI();

	//From Animatable
	virtual Class_ID ClassID() {return TessendorfOcean_CLASS_ID;}
	virtual SClass_ID SuperClassID() { return GEOMOBJECT_CLASS_ID; }
	virtual void GetClassName(TSTR& s) {s = GetString(IDS_CLASS_NAME);}

	virtual RefTargetHandle Clone( RemapDir& remap );

	virtual int NumParamBlocks() { return 1; }					// return number of ParamBlocks in this instance
	virtual IParamBlock2* GetParamBlock(int /*i*/) { return pblock2; } // return i'th ParamBlock
	virtual IParamBlock2* GetParamBlockByID(BlockID id) { return (pblock2->ID() == id) ? pblock2 : NULL; } // return id'd ParamBlock

	void DeleteThis() { delete this; }
};



class TessendorfOceanClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new TessendorfOcean(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return GEOMOBJECT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return TessendorfOcean_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("TessendorfOcean"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetTessendorfOceanDesc() { 
	static TessendorfOceanClassDesc TessendorfOceanDesc;
	return &TessendorfOceanDesc; 
}





enum { tessendorfocean_params };


//TODO: Add enums for various parameters
enum { 
	pb_spin,
};




static ParamBlockDesc2 tessendorfocean_param_blk ( tessendorfocean_params, _T("params"),  0, GetTessendorfOceanDesc(), 
	P_AUTO_CONSTRUCT + P_AUTO_UI, PBLOCK_REF, 
	//rollout
	IDD_PANEL, IDS_PARAMS, 0, 0, NULL,
	// params
	pb_spin, 			_T("spin"), 		TYPE_FLOAT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		0.1f, 
		p_range, 		0.0f,1000.0f, 
		p_ui, 			TYPE_SPINNER,		EDITTYPE_FLOAT, IDC_EDIT,	IDC_SPIN, 0.01f, 
		p_end,
	p_end
	);




//--- TessendorfOcean -------------------------------------------------------

TessendorfOcean::TessendorfOcean()
{
	GetTessendorfOceanDesc()->MakeAutoParamBlocks(this);
}

TessendorfOcean::~TessendorfOcean()
{
}

void TessendorfOcean::BeginEditParams(IObjParam* ip, ULONG flags, Animatable* prev)
{
	SimpleObject2::BeginEditParams(ip,flags,prev);
	GetTessendorfOceanDesc()->BeginEditParams(ip, this, flags, prev);
}

void TessendorfOcean::EndEditParams( IObjParam* ip, ULONG flags, Animatable* next )
{
	//TODO: Save plugin parameter values into class variables, if they are not hosted in ParamBlocks. 
	SimpleObject2::EndEditParams(ip,flags,next);
	GetTessendorfOceanDesc()->EndEditParams(ip, this, flags, next);
}

//From Object
BOOL TessendorfOcean::HasUVW() 
{ 
	//TODO: Return whether the object has UVW coordinates or not
	return TRUE; 
}

void TessendorfOcean::SetGenUVW(BOOL sw) 
{
	if (sw==HasUVW()) 
		return;
	//TODO: Set the plugin's internal value to sw
}

//Class for interactive creation of the object using the mouse
class TessendorfOceanCreateCallBack : public CreateMouseCallBack {
	IPoint2 sp0;              //First point in screen coordinates
	TessendorfOcean* ob; //Pointer to the object 
	Point3 p0;                //First point in world coordinates
public:	
	int proc( ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat);
	void SetObj(TessendorfOcean *obj) {ob = obj;}
};

int TessendorfOceanCreateCallBack::proc(ViewExp *vpt,int msg, int point, int /*flags*/, IPoint2 m, Matrix3& mat )
{
	//TODO: Implement the mouse creation code here
	if ( ! vpt || ! vpt->IsAlive() )
	{
		// why are we here
		DbgAssert(!_T("Invalid viewport!"));
		return FALSE;
	}

	if (msg == MOUSE_POINT || msg == MOUSE_MOVE) {
		switch(point) {
		case 0: // only happens with MOUSE_POINT msg
			ob->suspendSnap = TRUE;
			sp0 = m;
			p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
			mat.SetTrans(p0);
			break;
		//TODO: Add for the rest of points
		}
	} else {
		if (msg == MOUSE_ABORT) return CREATE_ABORT;
	}

	return TRUE;
}

static TessendorfOceanCreateCallBack TessendorfOceanCreateCB;

//From BaseObject
CreateMouseCallBack* TessendorfOcean::GetCreateMouseCallBack() 
{
	TessendorfOceanCreateCB.SetObj(this);
	return(&TessendorfOceanCreateCB);
}

//From SimpleObject
void TessendorfOcean::BuildMesh(TimeValue /*t*/)
{
	//TODO: Implement the code to build the mesh representation of the object
	//      using its parameter settings at the time passed. The plug-in should 
	//      use the data member mesh to store the built mesh.
	//      SimpleObject ivalid member should be updated. This can be done while
	//      retrieving values from pblock2.
	ivalid = FOREVER;
}

void TessendorfOcean::InvalidateUI() 
{
	// Hey! Update the param blocks
	pblock2->GetDesc()->InvalidateUI();
}

Object* TessendorfOcean::ConvertToType(TimeValue t, Class_ID obtype)
{
	//TODO: If the plugin can convert to a nurbs surface then check to see 
	//      whether obtype == EDITABLE_SURF_CLASS_ID and convert the object
	//      to nurbs surface and return the object
	//      If no special conversion is needed remove this implementation.
	
	return SimpleObject::ConvertToType(t,obtype);
}

int TessendorfOcean::CanConvertToType(Class_ID obtype)
{
	//TODO: Check for any additional types the plugin supports
	//      If no special conversion is needed remove this implementation.
	return SimpleObject::CanConvertToType(obtype);
}

// From Object
int TessendorfOcean::IntersectRay(TimeValue /*t*/, Ray& /*ray*/, float& /*at*/, Point3& /*norm*/)
{
	//TODO: Return TRUE after you implement this method
	return FALSE;
}

void TessendorfOcean::GetCollapseTypes(Tab<Class_ID>& clist,Tab<TSTR*>& nlist)
{
	Object::GetCollapseTypes(clist, nlist);
	//TODO: Append any any other collapse type the plugin supports
}

// From ReferenceTarget
RefTargetHandle TessendorfOcean::Clone(RemapDir& remap) 
{
	TessendorfOcean* newob = new TessendorfOcean();	
	//TODO: Make a copy all the data and also clone all the references
	newob->ReplaceReference(0,remap.CloneRef(pblock2));
	newob->ivalid.SetEmpty();
	BaseClone(this, newob, remap);
	return(newob);
}
