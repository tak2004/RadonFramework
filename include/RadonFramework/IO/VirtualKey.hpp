#ifndef RF_RF_VIRTUALKEY_HPP_HPP
#define RF_RF_VIRTUALKEY_HPP_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace IO {

enum class VirtualKey : RF_Type::UInt8
{
	NotSet,
	Escape,
	Space,
	PageUp,
	PageDown,
	Left,
	Up,
	Right,
	Down,
	ShiftLeft,
	ShiftRight,
	a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,
	A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_RF_VIRTUALKEY_HPP_HPP
