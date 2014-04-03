#ifndef RF_MATH_GEOMETRY_CUBICBEZIER_HPP
#define RF_MATH_GEOMETRY_CUBICBEZIER_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Collections/Generic/List.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>

namespace RadonFramework
{
    namespace Math
    {
        namespace Geometry
        {
            namespace Curve
            {
                enum Type
                {
                    Invalid,
                    Serpentine,
                    Loop,
                    CuspInflectionInfinity,
                    CuspWithCuspInfinity,
                    Quadratic,
                    Line
                };
            }

            template<class TIN=RFTYPE::Float32, class TOUT=RFTYPE::Float32>
            class CubicBezier
            {
                public:
                    CubicBezier();
                    CubicBezier(const Point2D<TIN>& Start, const Point2D<TIN>& StartControl,
                        const Point2D<TIN>& EndControl, const Point2D<TIN>& End);

                    Point2D<TIN> StartPoint;
                    Point2D<TIN> StartPointControl;
                    Point2D<TIN> EndPointControl;
                    Point2D<TIN> EndPoint;

                    static RFTYPE::Bool IsClockwise(const Point2D<TIN>& A,
                            const Point2D<TIN>& B, const Point2D<TIN>& C);
                    static RFTYPE::Bool IsInsideCircle(
                            const Point2D<TIN>& A, const Point2D<TIN>& B, 
                            const Point2D<TIN>& C, const Point2D<TIN>& D);

                    Curve::Type GetType(TOUT& Det1, TOUT& Det2, TOUT& Det3, TOUT& Det4)const;
                    void GenerateTriangles(
                        Collections::Generic::List<Vector<TOUT,4> >& Vertice,
                        Collections::Generic::List<Vector<TOUT,4> >& UVs);

                    void GeneratePoints(Collections::Generic::List<Point2D<TOUT> >& points,
                                        RFTYPE::UInt32 Steps);
            };
        }
    }
}

#define RMG RadonFramework::Math::Geometry
#define RCT RadonFramework::Core::Types
#define RCG RadonFramework::Collections::Generic

template<class TIN,class TOUT>
RMG::CubicBezier<TIN,TOUT>::CubicBezier()
{
}

template<class TIN,class TOUT>
RMG::CubicBezier<TIN,TOUT>::CubicBezier(const RMG::Point2D<TIN>& Start, const RMG::Point2D<TIN>& StartControl,
                              const RMG::Point2D<TIN>& EndControl, const RMG::Point2D<TIN>& End)
{
    StartPoint=Start;
    StartPointControl=StartControl;
    EndPointControl=EndControl;
    EndPoint=End;
}

template<class TIN,class TOUT>
RCT::Bool RMG::CubicBezier<TIN,TOUT>::IsClockwise(const Point2D<TIN>& A, const Point2D<TIN>& B, 
                                                  const Point2D<TIN>& C)
{
    TOUT edge0[2];
    TOUT edge1[2];

    edge0[0] = A.X - B.X;
    edge0[1] = A.Y - B.Y;
    edge1[0] = C.X - B.X;
    edge1[1] = C.Y - B.Y;

    return !(edge0[0] * edge1[1] - edge0[1] * edge1[0]) > 0.0f;
}

template<class TIN, class TOUT>
RCT::Bool RMG::CubicBezier<TIN,TOUT>::IsInsideCircle(const RMG::Point2D<TIN>& A, const RMG::Point2D<TIN>& B, 
                                                     const RMG::Point2D<TIN>& C, const RMG::Point2D<TIN>& D)
{
    TOUT dxsq=D.X*D.X;
    TOUT dysq=D.Y*D.Y;
    Matrix<TOUT,3,3> det;
    det.SetColumn(0,Vector<TOUT,3>(A.X - D.X, A.Y - D.Y, A.X * A.X - dxsq + A.Y * A.Y - dysq));
    det.SetColumn(1,Vector<TOUT,3>(B.X - D.X, B.Y - D.Y, B.X * B.X - dxsq + B.Y * B.Y - dysq));
    det.SetColumn(2,Vector<TOUT,3>(C.X - D.X, C.Y - D.Y, C.X * C.X - dxsq + C.Y * C.Y - dysq));
    TOUT r=det.Determinants();

    if (IsClockwise(A,B,C))
        return r>0.0f;
    else
        return !r>0.0f;
}

template<class TIN,class TOUT>
RMG::Curve::Type RMG::CubicBezier<TIN,TOUT>::GetType(TOUT& Det1, TOUT& Det2, TOUT& Det3, TOUT& Det4)const
{
    Matrix<TOUT,4,4> m3;
    m3.SetColumn(0,Vector<TOUT,4>(1.0,-3.0,3.0,-1.0));
    m3.SetColumn(1,Vector<TOUT,4>(0.0,3.0,-6.0,3.0));
    m3.SetColumn(2,Vector<TOUT,4>(0.0,0.0,3.0,-3.0));

    //calculate power basis c*m3=b
    Vector<TOUT,4> v1(StartPoint.X,StartPoint.Y,0,0);
    Vector<TOUT,4> v2(StartPointControl.X,StartPointControl.Y,0,0);
    Vector<TOUT,4> v3(EndPointControl.X,EndPointControl.Y,0,0);
    Vector<TOUT,4> v4(EndPoint.X,EndPoint.Y,0,0);

    Matrix<TOUT,4,4> b;
    b.SetColumn(0,v1);
    b.SetColumn(1,v2);
    b.SetColumn(2,v3);
    b.SetColumn(3,v4);
    b.Transpose();
    b*=m3;//use internal Transpose for faster calculation, do a transpose before and after
    b.Transpose();
    //calculate determiant of Det1,Det2,Det3 and Det4
    Matrix<TOUT,3,3> d;
    d.SetColumn(0,b[3]);
    d.SetColumn(1,b[2]);
    d.SetColumn(2,b[1]);
    Det1=d.Determinants();
    d.SetColumn(0,b[3]);
    d.SetColumn(1,b[2]);
    d.SetColumn(2,b[0]);
    Det2=-d.Determinants();
    d.SetColumn(0,b[3]);
    d.SetColumn(1,b[1]);
    d.SetColumn(2,b[0]);
    Det3=d.Determinants();
    d.SetColumn(0,b[2]);
    d.SetColumn(1,b[1]);
    d.SetColumn(2,b[0]);
    Det4=-d.Determinants();

    TOUT di=3.0*Det3*Det3-4.0*Det2*Det4;

    if (Det2!=0.0)
    {
        if(di>0.0)
            return RMG::Curve::Serpentine;
        if (di<0.0)
            return RMG::Curve::Loop;
        if (di==0.0)
            return RMG::Curve::CuspInflectionInfinity;
    }
    else
    {
        if (Det3!=0.0)
            return RMG::Curve::CuspWithCuspInfinity;
        else
        {
            if (Det4!=0.0)
                return RMG::Curve::Quadratic;
            else
                return RMG::Curve::Line;
        }
    }
    return RMG::Curve::Invalid;
}

template<class TIN,class TOUT>
void RMG::CubicBezier<TIN,TOUT>::GenerateTriangles(RCG::List<RMG::Vector<TOUT,4> >& Vertice,
                                                   RCG::List<RMG::Vector<TOUT,4> >& UVs)
{
    TOUT d1,d2,d3,d4;
    TOUT tmp,tl,sl,tm,sm,tn,sn;
    Curve::Type ct=GetType(d1,d2,d3,d4);
    TOUT s[16];
    Vector<TOUT,4> k0,k1,k2,k3,tmp_s,tmp_k,tmp_m,tmp_n;

    switch (ct)
    {
        case Curve::Serpentine:
        {
            tmp=1.0/sqrt(3.0)*sqrt(3.0*d3*d3-4.0*d2*d4);
            tl=d3+tmp;
            sl=2.0*d2;
            tm=d3-tmp;
            sm=sl;
            tn=1.0;
            sn=0.0;

            k0=Vector<TOUT,4>(tl*tm,tl*tl*tl,tm*tm*tm,1.0);
            k1=Vector<TOUT,4>(-sm*tl-sl*tm,-3.0*sl*tl*tl,-3.0*sm*tm*tm,0.0);
            k2=Vector<TOUT,4>(sl*sm,3.0*sl*sl*tl,3.0*sm*sm*tm,0.0);
            k3=Vector<TOUT,4>(0.0,-sl*sl*sl,-sm*sm*sm,0.0);

            if (d2<0.0)
            {
                sl*=-1.0;
                tl*=-1.0;
            }

            s[0]=k0[0];
            s[1]=k0[1];
            s[2]=k0[2];

            tmp_s=k1*(1.0/3.0);
            tmp_k=k0+tmp_s;
            s[3]=tmp_k[0];
            s[4]=tmp_k[1];
            s[5]=tmp_k[2];

            tmp_s=k1*(2.0/3.0);
            tmp_k=k2*(1.0/3.0);
            tmp_m=tmp_s+tmp_k;
            tmp_n=k0+tmp_m;
            s[6]=tmp_n[0];
            s[7]=tmp_n[1];
            s[8]=tmp_n[2];

            tmp_s=k0+k1;
            tmp_k=k2+k3;
            tmp_m=tmp_s+tmp_k;
            s[9]=tmp_m[0];
            s[10]=tmp_m[1];
            s[11]=tmp_m[2];

            Vertice.AddLast(Vector<TOUT,4>(StartPoint.X,StartPoint.Y));
            Vertice.AddLast(Vector<TOUT,4>(StartPointControl.X,StartPointControl.Y));
            Vertice.AddLast(Vector<TOUT,4>(EndPointControl.X,EndPointControl.Y));
            Vertice.AddLast(Vector<TOUT,4>(EndPoint.X,EndPoint.Y));
            UVs.AddLast(Vector<TOUT,4>(s[0],s[1],s[2]));
            UVs.AddLast(Vector<TOUT,4>(s[3],s[4],s[5]));
            UVs.AddLast(Vector<TOUT,4>(s[6],s[7],s[8]));
            UVs.AddLast(Vector<TOUT,4>(s[9],s[10],s[11]));
            break;
        }
        case Curve::Loop:
        {
            TOUT td,sd,te,se,tdsd,tese,bp;
            Vector<TOUT,4> sp,ep,spc,epc;
            sp=Vector<TOUT,4>(StartPoint.X,StartPoint.Y);
            ep=Vector<TOUT,4>(EndPoint.X,EndPoint.Y);
            spc=Vector<TOUT,4>(StartPointControl.X,StartPointControl.Y);
            epc=Vector<TOUT,4>(EndPointControl.X,EndPointControl.Y);

            tmp=sqrt(4.0*d2*d4-3.0*d3*d3);
            td=d3+tmp;
            sd=2.0*d2;
            te=d3-tmp;
            se=2.0*d2;

            tdsd=td/sd;
            tese=te/se;

            if (tdsd>0.0 && tdsd<1.0)
            bp=tdsd;
            if (tese>0.0 && tese<1.0)
            bp=tese;

            if (bp!=-1.0)//crack into 2 pieces
            {
                Vector<TOUT,4> A=sp*(1.0-bp)+spc*bp;
                Vector<TOUT,4> B=spc*(1.0-bp)+epc*bp;
                Vector<TOUT,4> C=epc*(1.0-bp)+ep*bp;
                Vector<TOUT,4> AB=A*(1.0-bp)+B*bp;
                Vector<TOUT,4> BC=B*(1.0-bp)+C*bp;
                Vector<TOUT,4> ABBC=AB*(1.0-bp)+BC*bp;

                CubicBezier<TIN,TOUT> a,b;
                a.StartPoint=StartPoint;
                a.StartPointControl.X=A[0];
                a.StartPointControl.Y=A[1];
                a.EndPointControl.X=AB[0];
                a.EndPointControl.Y=AB[1];
                a.EndPoint.X=ABBC[0];
                a.EndPoint.Y=ABBC[1];

                b.StartPoint.X=ABBC[0];
                b.StartPoint.Y=ABBC[1];
                b.StartPointControl.X=BC[0];
                b.StartPointControl.Y=BC[1];
                b.EndPointControl.X=C[0];
                b.EndPointControl.Y=C[1];
                b.EndPoint=EndPoint;

                a.GenerateTriangles(Vertice,UVs);
                b.GenerateTriangles(Vertice,UVs);
                return;
            }
            k0=Vector<TOUT,4>(td*te,td*td*te,td*te*te,1.0);
            k1=Vector<TOUT,4>(-se*td-sd*te,-se*td*td-2.0*sd*te*td,-sd*te*te-2.0*se*td*te,1.0);
            k2=Vector<TOUT,4>(sd*se, te*sd*sd+2.0*se*td*sd, td*se*se+2.0*sd*te*se, 1.0);
            k3=Vector<TOUT,4>(0.0,-sd*sd*se,-sd*se*se,1.0);
            s[0]=k0[0];
            s[1]=k0[1];
            s[2]=k0[2];

            tmp_s=k1*(1.0/3.0);
            tmp_k=k0+tmp_s;
            s[3]=tmp_k[0];
            s[4]=tmp_k[1];
            s[5]=tmp_k[2];

            tmp_s=k1*(2.0/3.0);
            tmp_k=k2*(1.0/3.0);
            tmp_m=tmp_s+tmp_k;
            tmp_n=k0+tmp_m;
            s[6]=tmp_n[0];
            s[7]=tmp_n[1];
            s[8]=tmp_n[2];

            tmp_s=k0+k1;
            tmp_k=k2+k3;
            tmp_m=tmp_s+tmp_k;
            s[9]=tmp_m[0];
            s[10]=tmp_m[1];
            s[11]=tmp_m[2];

            Vertice.AddLast(sp);
            Vertice.AddLast(spc);
            Vertice.AddLast(epc);
            Vertice.AddLast(ep);
            UVs.AddLast(Vector<TOUT,4>(s[0],s[1],s[2],0.0));
            UVs.AddLast(Vector<TOUT,4>(s[3],s[4],s[5],0.0));
            UVs.AddLast(Vector<TOUT,4>(s[6],s[7],s[8],0.0));
            UVs.AddLast(Vector<TOUT,4>(s[9],s[10],s[11],0.0));
            break;
        }
        case Curve::CuspInflectionInfinity:
        case Curve::CuspWithCuspInfinity:
        case Curve::Quadratic:
        case Curve::Line:
        case Curve::Invalid:
            break;
    }
}

template<class TIN,class TOUT>
void RMG::CubicBezier<TIN,TOUT>::GeneratePoints(RCG::List<RMG::Point2D<TOUT> >& points, RCT::UInt32 Steps)
{
    for(RCT::UInt32 i = 1; i <= Steps; i++)
    {
        RCT::Float32 t = static_cast<RCT::Float32>(i) / Steps;
        RMG::Point2D<TOUT> T(t,t);
        RMG::Point2D<TOUT> T1(1.0f-t,1.0f-t);

        RMG::Point2D<TOUT> U = T1 * StartPoint + T * StartPointControl;
        RMG::Point2D<TOUT> V = T1 * StartPointControl + T * EndPointControl;
        RMG::Point2D<TOUT> W = T1 * EndPointControl + T * EndPoint;

        RMG::Point2D<TOUT> M = T1 * U + T * V;
        RMG::Point2D<TOUT> N = T1 * V + T * W;

        points.AddLast(T1 * M + T * N);
    }
}

#undef RMG
#undef RCT
#undef RCG

#endif // RF_MATH_GEOMETRY_CUBICBEZIER_HPP