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
    static IObjParam *ip; // Access to the interface

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
    pb_width,
    pb_length,
    pb_width_segs,
    pb_length_segs,
    pb_amplitude,
    pb_min_wave_size,
    pb_wind_speed,
    pb_wind_direction,
    pb_choppiness,
    pb_seed
};




static ParamBlockDesc2 tessendorfocean_param_blk ( tessendorfocean_params, _T("params"),  0, GetTessendorfOceanDesc(), 
    P_AUTO_CONSTRUCT + P_AUTO_UI, PBLOCK_REF, 
    //rollout
    IDD_PANEL, IDS_PARAMS, 0, 0, NULL,
    // params
    pb_width,			_T("width"),		TYPE_FLOAT,		P_ANIMATABLE,		IDS_WIDTH,
        p_default,		100.0f,
        p_range,		0.1f,10000.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_FLOAT,	IDC_WIDTH_EDIT,		IDC_WIDTH_SPIN,			0.1f,
        p_end,
    pb_length,			_T("length"),		TYPE_FLOAT,		P_ANIMATABLE,		IDS_LENGTH,
        p_default,		100.0f,
        p_range,		0.1f,10000.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_FLOAT,	IDC_LENGTH_EDIT,	IDC_LENGTH_SPIN,		0.1f,
        p_end,
    pb_width_segs,		_T("width_segs"),	TYPE_FLOAT,		0,					IDS_WIDTH_SEGS,
        p_default,		100.0f,
        p_range,		10.0f,1000.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_INT,	IDC_WIDTH_SEGS_EDIT,IDC_WIDTH_SEGS_SPIN,	1.0f,
        p_end,
    pb_length_segs,		_T("length_segs"),	TYPE_FLOAT,		0,					IDS_LENGTH_SEGS,
        p_default,		100.0f,
        p_range,		10.0f,1000.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_INT,	IDC_LENGTH_SEGS_EDIT,IDC_LENGTH_SEGS_SPIN,	1.0f,
        p_end,
    pb_amplitude, 		_T("amplitude"), 	TYPE_FLOAT, 	P_ANIMATABLE, 		IDS_AMPLITUDE, 
        p_default, 		0.001f, 
        p_range, 		0.0f,0.1f, 
        p_ui, 			TYPE_SPINNER,		EDITTYPE_FLOAT, IDC_AMPLITUDE_EDIT,	IDC_AMPLITUDE_SPIN,		0.001f, 
        p_end,
    pb_min_wave_size,	_T("min_wave_size"),TYPE_FLOAT,		P_ANIMATABLE,		IDS_MIN_SIZE,
        p_default,		1.0f,
        p_range,		0.0f,50.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_FLOAT,	IDC_MIN_SIZE_EDIT,	IDC_MIN_SIZE_SPIN,		0.1f,
        p_end,
    pb_wind_speed,		_T("wind_speed"),	TYPE_FLOAT,		P_ANIMATABLE,		IDS_SPEED,
        p_default,		2.0f,
        p_range,		0.0f,20.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_FLOAT,	IDC_SPEED_EDIT,		IDC_SPEED_SPIN,			0.1f,
        p_end,
    pb_wind_direction,	_T("wind_dir"),		TYPE_ANGLE,		P_ANIMATABLE,		IDS_DIRECTION,
        p_default,		0.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_FLOAT,	IDC_DIRECTION_EDIT,	IDC_DIRECTION_SPIN,		1.0f,
        p_end,
    pb_choppiness,		_T("choppiness"),	TYPE_FLOAT,		P_ANIMATABLE,		IDS_CHOPPINESS,
        p_default,		0.5f,
        p_range,		0.0f,2.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_FLOAT,	IDC_CHOPPINESS_EDIT,IDC_CHOPPINESS_SPIN,	0.1f,
        p_end,
    pb_seed,			_T("seed"),			TYPE_FLOAT,		0,		IDS_SEED,
        p_default,		1.0f,
        p_range,		1.0f,4000000000.0f,
        p_ui,			TYPE_SPINNER,		EDITTYPE_FLOAT,	IDC_SEED_EDIT,		IDC_SEED_SPIN,			1.0f,
        p_end,
    p_end
    );


IObjParam *TessendorfOcean::ip = NULL;


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
    this->ip = ip;

    SimpleObject2::BeginEditParams(ip,flags,prev);
    GetTessendorfOceanDesc()->BeginEditParams(ip, this, flags, prev);
}

void TessendorfOcean::EndEditParams( IObjParam* ip, ULONG flags, Animatable* next )
{
    //TODO: Save plugin parameter values into class variables, if they are not hosted in ParamBlocks. 
    SimpleObject2::EndEditParams(ip,flags,next);
    GetTessendorfOceanDesc()->EndEditParams(ip, this, flags, next);

    this->ip = NULL;
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
    IPoint2 sp0;            //First point in screen coordinates
    TessendorfOcean* ob;	//Pointer to the object 
    Point3 p0;				//First point in world coordinates
    Point3 p1;				//Second point in world coordinates
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

                //Set a default overall size in the parameter block
                ob->pblock2->SetValue(pb_width, ob->ip->GetTime(), 0.0f);
                ob->pblock2->SetValue(pb_length, ob->ip->GetTime(), 0.0f);
                break;
            case 1:
            {
                ob->suspendSnap = TRUE; 
                p1 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
                Point3 diff = p1 - p0;
                mat.SetTrans(p0 + diff / 2.0f);
                
                //Set the overall size in parameter block
                ob->pblock2->SetValue(pb_width, ob->ip->GetTime(), abs(diff.x));
                ob->pblock2->SetValue(pb_length, ob->ip->GetTime(), abs(diff.y));

                //Invalidate and display the mesh in the viewport
                tessendorfocean_param_blk.InvalidateUI();
                break;
            }
            case 2:
            {
                return CREATE_STOP;
            }
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
void TessendorfOcean::BuildMesh(TimeValue t)
{
    //TODO: Implement the code to build the mesh representation of the object
    //      using its parameter settings at the time passed. The plug-in should 
    //      use the data member mesh to store the built mesh.
    //      SimpleObject ivalid member should be updated. This can be done while
    //      retrieving values from pblock2.
    ivalid = FOREVER;

    float length, width;
    pblock2->GetValue(pb_length, t, length, ivalid );
    pblock2->GetValue(pb_width, t, width, ivalid );

    mesh.setNumVerts(4);
    mesh.setNumFaces(2);
    mesh.setVert(0, -width / 2.0f, -length / 2.0f, 0.0f);
    mesh.setVert(1, -width / 2.0f, length / 2.0f, 0.0f);
    mesh.setVert(2, width / 2.0f, length / 2.0f, 0.0f);
    mesh.setVert(3, width / 2.0f, -length / 2.0f, 0.0f);
    mesh.faces[0].setVerts(0, 1, 2);
    mesh.faces[0].setEdgeVisFlags(1,1,0);
    mesh.faces[0].setSmGroup(0);
    mesh.faces[1].setVerts(2, 3, 0);
    mesh.faces[1].setEdgeVisFlags(1,1,0);
    mesh.faces[1].setSmGroup(0);
    
    mesh.InvalidateGeomCache();
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
