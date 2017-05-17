#include <librg/utils/math.h>

HINLINE float
HMM_SinF(float Angle)
{
    float Result = 0.0f;

    Result = HMM_SINF(Angle);
    return (Result);
}

HINLINE float
HMM_CosF(float Angle)
{
    float Result = 0.0f;

    Result = HMM_COSF(Angle);
    return (Result);
}

HINLINE float
HMM_TanF(float Radians)
{
    float Result = 0.0f;

    Result = HMM_TANF(Radians);
    return (Result);
}

HINLINE float
HMM_ACosF(float Radians)
{
    float Result = 0.0f;

    Result = HMM_ACOSF(Radians);
    return (Result);
}

HINLINE float
HMM_ATanF(float Radians)
{
    float Result = 0.0f;

    Result = HMM_ATANF(Radians);
    return (Result);
}

HINLINE float
HMM_Atan2F(float Left, float Right)
{
    float Result = 0.0f;

    Result = HMM_ATAN2F(Left, Right);
    return (Result);
}

HINLINE float
HMM_ExpF(float Float)
{
    float Result = 0.0f;

    Result = HMM_EXPF(Float);
    return (Result);
}

HINLINE float
HMM_LogF(float Float)
{
    float Result = 0.0f;

    Result = HMM_LOGF(Float);
    return (Result);
}

HINLINE float
HMM_ToRadians(float Degrees)
{
    float Result = 0.0f;

    Result = Degrees * (HMM_PI32 / 180.0f);
    return (Result);
}

HINLINE float
HMM_SquareRootF(float Value)
{
    float Result = 0.0f;

#ifdef HANDMADE_MATH_NO_SSE
    Result = sqrtf(Value);
#else        
    __m128 In = _mm_set_ss(Value);
    __m128 Out = _mm_sqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#endif 

    return(Result);
}

HINLINE float
HMM_RSquareRootF(float Value)
{
    float Result = 0.0f;

#ifdef HANDMADE_MATH_NO_SSE
    Result = 1.0f / HMM_SqrtF(Value);
#else        
    __m128 In = _mm_set_ss(Value);
    __m128 Out = _mm_rsqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#endif

    return(Result);
}

HINLINE float
HMM_LengthSquaredVec2(hmm_vec2 A)
{
    float Result = 0.0f;

    Result = HMM_DotVec2(A, A);

    return(Result);
}

HINLINE float
HMM_LengthSquaredVec3(hmm_vec3 A)
{
    float Result = 0.0f;

    Result = HMM_DotVec3(A, A);

    return (Result);
}

HINLINE float
HMM_LengthSquaredVec4(hmm_vec4 A)
{
    float Result = 0.0f;

    Result = HMM_DotVec4(A, A);

    return(Result);
}

HINLINE float
HMM_LengthVec2(hmm_vec2 A)
{
    float Result = 0.0f;

    Result = HMM_SquareRootF(HMM_LengthSquaredVec2(A));

    return(Result);
}

HINLINE float
HMM_LengthVec3(hmm_vec3 A)
{
    float Result = 0.0f;

    Result = HMM_SquareRootF(HMM_LengthSquaredVec3(A));

    return (Result);
}

HINLINE float
HMM_LengthVec4(hmm_vec4 A)
{
    float Result = 0.0f;

    Result = HMM_SquareRootF(HMM_LengthSquaredVec4(A));

    return(Result);
}

HINLINE float
HMM_Power(float Base, int Exponent)
{
    float Result = 1.0f;
    float Mul = Exponent < 0 ? 1.f / Base : Base;
    unsigned int X = Exponent < 0 ? -Exponent : Exponent;
    while (X)
    {
        if (X & 1)
        {
            Result *= Mul;
        }

        Mul *= Mul;
        X >>= 1;
    }

    return (Result);
}

HINLINE float
HMM_PowerF(float Base, float Exponent)
{
    return HMM_EXPF(Exponent * HMM_LOGF(Base));
}

HINLINE float
HMM_Lerp(float A, float Time, float B)
{
    float Result = 0;

    Result = (1.0f - Time) * A + Time * B;
    return (Result);
}

HINLINE float
HMM_Clamp(float Min, float Value, float Max)
{
    float Result = Value;

    if (Result < Min)
    {
        Result = Min;
    }
    else if (Result > Max)
    {
        Result = Max;
    }

    return (Result);
}

HINLINE hmm_vec2
HMM_NormalizeVec2(hmm_vec2 A)
{
    hmm_vec2 Result = { 0 };

    float VectorLength = HMM_LengthVec2(A);

    Result.X = A.X * (1.0f / VectorLength);
    Result.Y = A.Y * (1.0f / VectorLength);

    return (Result);
}

HINLINE hmm_vec3
HMM_NormalizeVec3(hmm_vec3 A)
{
    hmm_vec3 Result = { 0 };

    float VectorLength = HMM_LengthVec3(A);

    Result.X = A.X * (1.0f / VectorLength);
    Result.Y = A.Y * (1.0f / VectorLength);
    Result.Z = A.Z * (1.0f / VectorLength);

    return (Result);
}

HINLINE hmm_vec4
HMM_NormalizeVec4(hmm_vec4 A)
{
    hmm_vec4 Result = { 0 };

    float VectorLength = HMM_LengthVec4(A);

    Result.X = A.X * (1.0f / VectorLength);
    Result.Y = A.Y * (1.0f / VectorLength);
    Result.Z = A.Z * (1.0f / VectorLength);
    Result.W = A.W * (1.0f / VectorLength);

    return (Result);
}

HINLINE float
HMM_DotVec2(hmm_vec2 VecOne, hmm_vec2 VecTwo)
{
    float Result = 0.0f;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y);

    return (Result);
}

HINLINE float
HMM_DotVec3(hmm_vec3 VecOne, hmm_vec3 VecTwo)
{
    float Result = 0.0f;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z);

    return (Result);
}

HINLINE float
HMM_DotVec4(hmm_vec4 VecOne, hmm_vec4 VecTwo)
{
    float Result = 0.0f;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z) + (VecOne.W * VecTwo.W);

    return (Result);
}

HINLINE hmm_vec3
HMM_Cross(hmm_vec3 VecOne, hmm_vec3 VecTwo)
{
    hmm_vec3 Result = { 0 };

    Result.X = (VecOne.Y * VecTwo.Z) - (VecOne.Z * VecTwo.Y);
    Result.Y = (VecOne.Z * VecTwo.X) - (VecOne.X * VecTwo.Z);
    Result.Z = (VecOne.X * VecTwo.Y) - (VecOne.Y * VecTwo.X);

    return (Result);
}

HINLINE hmm_vec2
HMM_Vec2(float X, float Y)
{
    hmm_vec2 Result = { 0 };

    Result.X = X;
    Result.Y = Y;

    return (Result);
}

HINLINE hmm_vec2
HMM_Vec2i(int X, int Y)
{
    hmm_vec2 Result = { 0 };

    Result.X = (float)X;
    Result.Y = (float)Y;

    return (Result);
}

HINLINE hmm_vec3
HMM_Vec3(float X, float Y, float Z)
{
    hmm_vec3 Result = { 0 };

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;

    return (Result);
}

HINLINE hmm_vec3
HMM_Vec3i(int X, int Y, int Z)
{
    hmm_vec3 Result = { 0 };

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;

    return (Result);
}

HINLINE hmm_vec4
HMM_Vec4(float X, float Y, float Z, float W)
{
    hmm_vec4 Result = { 0 };

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;

    return (Result);
}

HINLINE hmm_vec4
HMM_Vec4i(int X, int Y, int Z, int W)
{
    hmm_vec4 Result = { 0 };

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;
    Result.W = (float)W;

    return (Result);
}

HINLINE hmm_vec4
HMM_Vec4v(hmm_vec3 Vector, float W)
{
    hmm_vec4 Result = { 0 };

    Result.XYZ = Vector;
    Result.W = W;

    return (Result);
}

HINLINE hmm_vec2
HMM_AddVec2(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;

    return (Result);
}

HINLINE hmm_vec3
HMM_AddVec3(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;

    return (Result);
}

HINLINE hmm_vec4
HMM_AddVec4(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;

    return (Result);
}

HINLINE hmm_vec2
HMM_SubtractVec2(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;

    return (Result);
}

HINLINE hmm_vec3
HMM_SubtractVec3(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;

    return (Result);
}

HINLINE hmm_vec4
HMM_SubtractVec4(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;

    return (Result);
}

HINLINE hmm_vec2
HMM_MultiplyVec2(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;

    return (Result);
}

HINLINE hmm_vec2
HMM_MultiplyVec2f(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = { 0 };

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;

    return (Result);
}

HINLINE hmm_vec3
HMM_MultiplyVec3(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;

    return (Result);
}

HINLINE hmm_vec3
HMM_MultiplyVec3f(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = { 0 };

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;

    return (Result);
}

HINLINE hmm_vec4
HMM_MultiplyVec4(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;
    Result.W = Left.W * Right.W;

    return (Result);
}

HINLINE hmm_vec4
HMM_MultiplyVec4f(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = { 0 };

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;
    Result.W = Left.W * Right;

    return (Result);
}

HINLINE hmm_vec2
HMM_DivideVec2(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;

    return (Result);
}

HINLINE hmm_vec2
HMM_DivideVec2f(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = { 0 };

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;

    return (Result);
}

HINLINE hmm_vec3
HMM_DivideVec3(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;

    return (Result);
}

HINLINE hmm_vec3
HMM_DivideVec3f(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = { 0 };

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;

    return (Result);
}

HINLINE hmm_vec4
HMM_DivideVec4(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;
    Result.W = Left.W / Right.W;

    return (Result);
}

HINLINE hmm_vec4
HMM_DivideVec4f(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = { 0 };

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;
    Result.W = Left.W / Right;

    return (Result);
}

HINLINE hmm_mat4
HMM_Mat4(void)
{
    hmm_mat4 Result = { 0 };

    return (Result);
}

HINLINE hmm_mat4
HMM_Mat4d(float Diagonal)
{
    hmm_mat4 Result = HMM_Mat4();

    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;
    Result.Elements[3][3] = Diagonal;

    return (Result);
}

HINLINE hmm_mat4
HMM_AddMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for (Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for (Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] + Right.Elements[Columns][Rows];
        }
    }

    return (Result);
}

HINLINE hmm_mat4
HMM_SubtractMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for (Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for (Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] - Right.Elements[Columns][Rows];
        }
    }

    return (Result);
}

HINLINE hmm_mat4
HMM_MultiplyMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for (Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for (Rows = 0; Rows < 4; ++Rows)
        {
            float Sum = 0;
            int CurrentMatrice;
            for (CurrentMatrice = 0; CurrentMatrice < 4; ++CurrentMatrice)
            {
                Sum += Left.Elements[CurrentMatrice][Rows] * Right.Elements[Columns][CurrentMatrice];
            }

            Result.Elements[Columns][Rows] = Sum;
        }
    }

    return (Result);
}

HINLINE hmm_mat4
HMM_MultiplyMat4f(hmm_mat4 Matrix, float Scalar)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for (Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for (Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] * Scalar;
        }
    }

    return (Result);
}

HINLINE hmm_vec4
HMM_MultiplyMat4ByVec4(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result = { 0 };

    int Columns, Rows;
    for (Rows = 0; Rows < 4; ++Rows)
    {
        float Sum = 0;
        for (Columns = 0; Columns < 4; ++Columns)
        {
            Sum += Matrix.Elements[Columns][Rows] * Vector.Elements[Columns];
        }

        Result.Elements[Rows] = Sum;
    }

    return (Result);
}

HINLINE hmm_mat4
HMM_DivideMat4f(hmm_mat4 Matrix, float Scalar)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for (Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for (Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] / Scalar;
        }
    }

    return (Result);
}

HINLINE hmm_mat4
HMM_Transpose(hmm_mat4 Matrix)
{
    hmm_mat4 Result = HMM_Mat4();

    int Columns;
    for (Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for (Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Rows][Columns] = Matrix.Elements[Columns][Rows];
        }
    }

    return (Result);
}

HINLINE hmm_mat4
HMM_Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 2.0f / (Near - Far);

    Result.Elements[3][0] = (Left + Right) / (Left - Right);
    Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[3][2] = (Far + Near) / (Near - Far);

    return (Result);
}

HINLINE hmm_mat4
HMM_Perspective(float FOV, float AspectRatio, float Near, float Far)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    float TanThetaOver2 = HMM_TanF(FOV * (HMM_PI32 / 360.0f));

    Result.Elements[0][0] = 1.0f / TanThetaOver2;
    Result.Elements[1][1] = AspectRatio / TanThetaOver2;
    Result.Elements[2][3] = -1.0f;
    Result.Elements[2][2] = (Near + Far) / (Near - Far);
    Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);
    Result.Elements[3][3] = 0.0f;

    return (Result);
}

HINLINE hmm_mat4
HMM_Translate(hmm_vec3 Translation)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    Result.Elements[3][0] = Translation.X;
    Result.Elements[3][1] = Translation.Y;
    Result.Elements[3][2] = Translation.Z;

    return (Result);
}

HINLINE hmm_mat4
HMM_Rotate(float Angle, hmm_vec3 Axis)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    Axis = HMM_NormalizeVec3(Axis);

    float SinTheta = HMM_SinF(HMM_ToRadians(Angle));
    float CosTheta = HMM_CosF(HMM_ToRadians(Angle));
    float CosValue = 1.0f - CosTheta;

    Result.Elements[0][0] = (Axis.X * Axis.X * CosValue) + CosTheta;
    Result.Elements[0][1] = (Axis.X * Axis.Y * CosValue) + (Axis.Z * SinTheta);
    Result.Elements[0][2] = (Axis.X * Axis.Z * CosValue) - (Axis.Y * SinTheta);

    Result.Elements[1][0] = (Axis.Y * Axis.X * CosValue) - (Axis.Z * SinTheta);
    Result.Elements[1][1] = (Axis.Y * Axis.Y * CosValue) + CosTheta;
    Result.Elements[1][2] = (Axis.Y * Axis.Z * CosValue) + (Axis.X * SinTheta);

    Result.Elements[2][0] = (Axis.Z * Axis.X * CosValue) + (Axis.Y * SinTheta);
    Result.Elements[2][1] = (Axis.Z * Axis.Y * CosValue) - (Axis.X * SinTheta);
    Result.Elements[2][2] = (Axis.Z * Axis.Z * CosValue) + CosTheta;

    return (Result);
}

HINLINE hmm_mat4
HMM_Scale(hmm_vec3 Scale)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);

    Result.Elements[0][0] = Scale.X;
    Result.Elements[1][1] = Scale.Y;
    Result.Elements[2][2] = Scale.Z;

    return (Result);
}

HINLINE hmm_mat4
HMM_LookAt(hmm_vec3 Eye, hmm_vec3 Center, hmm_vec3 Up)
{
    hmm_mat4 Result = { 0 };

    hmm_vec3 F = HMM_NormalizeVec3(HMM_SubtractVec3(Center, Eye));
    hmm_vec3 S = HMM_NormalizeVec3(HMM_Cross(F, Up));
    hmm_vec3 U = HMM_Cross(S, F);

    Result.Elements[0][0] = S.X;
    Result.Elements[0][1] = U.X;
    Result.Elements[0][2] = -F.X;

    Result.Elements[1][0] = S.Y;
    Result.Elements[1][1] = U.Y;
    Result.Elements[1][2] = -F.Y;

    Result.Elements[2][0] = S.Z;
    Result.Elements[2][1] = U.Z;
    Result.Elements[2][2] = -F.Z;

    Result.Elements[3][0] = -HMM_DotVec3(S, Eye);
    Result.Elements[3][1] = -HMM_DotVec3(U, Eye);
    Result.Elements[3][2] = HMM_DotVec3(F, Eye);
    Result.Elements[3][3] = 1.0f;

    return (Result);
}


HINLINE hmm_quaternion
HMM_Quaternion(float X, float Y, float Z, float W)
{
    hmm_quaternion Result = { 0 };

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;

    return(Result);
}

HINLINE hmm_quaternion
HMM_QuaternionV4(hmm_vec4 Vector)
{
    hmm_quaternion Result = { 0 };

    Result.X = Vector.X;
    Result.Y = Vector.Y;
    Result.Z = Vector.Z;
    Result.W = Vector.W;

    return(Result);
}

HINLINE hmm_quaternion
HMM_AddQuaternion(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;

    return(Result);
}

HINLINE hmm_quaternion
HMM_SubtractQuaternion(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;

    return(Result);
}

HINLINE hmm_quaternion
HMM_MultiplyQuaternion(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result.X = (Left.X * Right.W) + (Left.Y * Right.Z) - (Left.Z * Right.Y) + (Left.W * Right.X);
    Result.Y = (-Left.X * Right.Z) + (Left.Y * Right.W) + (Left.Z * Right.X) + (Left.W * Right.Y);
    Result.Z = (Left.X * Right.Y) - (Left.Y * Right.X) + (Left.Z * Right.W) + (Left.W * Right.Z);
    Result.W = (-Left.X * Right.X) - (Left.Y * Right.Y) - (Left.Z * Right.Z) + (Left.W * Right.W);

    return(Result);
}

HINLINE hmm_quaternion
HMM_MultiplyQuaternionF(hmm_quaternion Left, float Multiplicative)
{
    hmm_quaternion Result = { 0 };

    Result.X = Left.X * Multiplicative;
    Result.Y = Left.Y * Multiplicative;
    Result.Z = Left.Z * Multiplicative;
    Result.W = Left.W * Multiplicative;

    return(Result);
}

HINLINE hmm_quaternion
HMM_DivideQuaternionF(hmm_quaternion Left, float Dividend)
{
    hmm_quaternion Result = { 0 };

    Result.X = Left.X / Dividend;
    Result.Y = Left.Y / Dividend;
    Result.Z = Left.Z / Dividend;
    Result.W = Left.W / Dividend;

    return(Result);
}

HINLINE hmm_quaternion
HMM_InverseQuaternion(hmm_quaternion Left)
{
    hmm_quaternion Conjugate = { 0 };
    hmm_quaternion Result = { 0 };
    float Norm = 0;
    float NormSquared = 0;

    Conjugate.X = -Left.X;
    Conjugate.Y = -Left.Y;
    Conjugate.Z = -Left.Z;
    Conjugate.W = Left.W;

    Norm = HMM_SquareRootF(HMM_DotQuaternion(Left, Left));
    NormSquared = Norm * Norm;

    Result.X = Conjugate.X / NormSquared;
    Result.Y = Conjugate.Y / NormSquared;
    Result.Z = Conjugate.Z / NormSquared;
    Result.W = Conjugate.W / NormSquared;

    return(Result);
}

HINLINE float
HMM_DotQuaternion(hmm_quaternion Left, hmm_quaternion Right)
{
    float Result = 0.0f;

    Result = (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z) + (Left.W * Right.W);

    return(Result);
}

HINLINE hmm_quaternion
HMM_NormalizeQuaternion(hmm_quaternion Left)
{
    hmm_quaternion Result = { 0 };

    float Length = HMM_SquareRootF(HMM_DotQuaternion(Left, Left));
    Result = HMM_DivideQuaternionF(Left, Length);

    return(Result);
}

HINLINE hmm_quaternion
HMM_NLerp(hmm_quaternion Left, float Time, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result.X = HMM_Lerp(Left.X, Time, Right.X);
    Result.Y = HMM_Lerp(Left.Y, Time, Right.Y);
    Result.Z = HMM_Lerp(Left.Z, Time, Right.Z);
    Result.W = HMM_Lerp(Left.W, Time, Right.W);

    Result = HMM_NormalizeQuaternion(Result);

    return(Result);
}

/*
HINLINE hmm_quaternion
HMM_Slerp(hmm_quaternion Left, float Time, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };
    hmm_quaternion QuaternionLeft = { 0 };
    hmm_quaternion QuaternionRight = { 0 };

    float Cos_Theta = HMM_DotQuaternion(Left, Right);
    float Angle = HMM_ACosF(Cos_Theta);

    float S1 = HMM_SinF((1.0f - Time) * Angle);
    float S2 = HMM_SinF(Time * Angle);
    float Is = 1.0f / HMM_SinF(Angle);

    QuaternionLeft = HMM_MultiplyQuaternionF(Left, S1);
    QuaternionRight = HMM_MultiplyQuaternionF(Right, S2);

    Result = HMM_AddQuaternion(QuaternionLeft, QuaternionRight);
    Result = HMM_MultiplyQuaternionF(Result, Is);

    return(Result);
}
*/
HINLINE hmm_quaternion
HMM_QuaternionFromVec3(hmm_vec3 i)
{
    hmm_quaternion q;

    float pitch = i.X;
    float roll  = i.Y;
    float yaw   = i.Z;

    float t0 = HMM_CosF(yaw * 0.5);
    float t1 = HMM_SinF(yaw * 0.5);
    float t2 = HMM_CosF(roll * 0.5);
    float t3 = HMM_SinF(roll * 0.5);
    float t4 = HMM_CosF(pitch * 0.5);
    float t5 = HMM_SinF(pitch * 0.5);

    q.W = t0 * t2 * t4 + t1 * t3 * t5;
    q.X = t0 * t3 * t4 - t1 * t2 * t5;
    q.Y = t0 * t2 * t5 + t1 * t3 * t4;
    q.Z = t1 * t2 * t4 - t0 * t3 * t5;

    return q;
}

HINLINE hmm_quaternion
HMM_Slerp(hmm_quaternion v0, float t, hmm_quaternion v1) {
    // Only unit quaternions are valid rotations.
    // Normalize to avoid undefined behavior.
    v0 = HMM_NormalizeQuaternion(v0);
    v1 = HMM_NormalizeQuaternion(v1);

    // Compute the cosine of the angle between the two vectors.
    float dot = HMM_DotQuaternion(v0, v1);

    const double DOT_THRESHOLD = 0.9995;
    if (HMM_ABS(dot) > DOT_THRESHOLD) {
        // If the inputs are too close for comfort, linearly interpolate
        // and normalize the result.

        hmm_quaternion result = HMM_AddQuaternion(v0, HMM_MultiplyQuaternionF(HMM_SubtractQuaternion(v1, v0), t));
        return HMM_NormalizeQuaternion(result);
    }

    // If the dot product is negative, the quaternions
    // have opposite handed-ness and slerp won't take
    // the shorter path. Fix by reversing one quaternion.
    if (dot < 0.0f) {
        v1 = HMM_Quaternion(-v1.X, -v1.Y, -v1.Z, -v1.W);
        dot = -dot;
    }

    dot = HMM_Clamp(-1, dot, 1);           // Robustness: Stay within domain of acos()
    float theta_0 = HMM_ACosF(dot);  // theta_0 = angle between input vectors
    float theta = theta_0*t;    // theta = angle between v0 and result

    hmm_quaternion v2 = HMM_SubtractQuaternion(v1, HMM_MultiplyQuaternionF(v0, dot));
    v2 = HMM_NormalizeQuaternion(v2);              // { v0, v2 } is now an orthonormal basis

    return HMM_AddQuaternion(HMM_MultiplyQuaternionF(v0, HMM_CosF(theta)), HMM_MultiplyQuaternionF(v2, HMM_SinF(theta)));
}

HINLINE hmm_mat4
HMM_QuaternionToMat4(hmm_quaternion Left)
{
    hmm_mat4 Result = { 0 };
    Result = HMM_Mat4d(1);

    hmm_quaternion NormalizedQuaternion = HMM_NormalizeQuaternion(Left);

    float XX, YY, ZZ,
        XY, XZ, YZ,
        WX, WY, WZ;

    XX = NormalizedQuaternion.X * NormalizedQuaternion.X;
    YY = NormalizedQuaternion.Y * NormalizedQuaternion.Y;
    ZZ = NormalizedQuaternion.Z * NormalizedQuaternion.Z;
    XY = NormalizedQuaternion.X * NormalizedQuaternion.Y;
    XZ = NormalizedQuaternion.X * NormalizedQuaternion.Z;
    YZ = NormalizedQuaternion.Y * NormalizedQuaternion.Z;
    WX = NormalizedQuaternion.W * NormalizedQuaternion.X;
    WY = NormalizedQuaternion.W * NormalizedQuaternion.Y;
    WZ = NormalizedQuaternion.W * NormalizedQuaternion.Z;

    Result.Elements[0][0] = 1.0f - 2.0f * (YY + ZZ);
    Result.Elements[0][1] = 2.0f * (XY + WZ);
    Result.Elements[0][2] = 2.0f * (XZ - WY);

    Result.Elements[1][0] = 2.0f * (XY - WZ);
    Result.Elements[1][1] = 1.0f - 2.0f * (XX + ZZ);
    Result.Elements[1][2] = 2.0f * (YZ + WX);

    Result.Elements[2][0] = 2.0f * (XZ + WY);
    Result.Elements[2][1] = 2.0f * (YZ - WX);
    Result.Elements[2][2] = 1.0f - 2.0f * (XX + YY);

    return(Result);
}

HINLINE hmm_quaternion
HMM_QuaternionFromAxisAngle(hmm_vec3 Axis, float AngleOfRotation)
{
    hmm_quaternion Result = { 0 };
    float AxisNorm = 0;
    float SineOfRotation = 0;
    hmm_vec3 RotatedVector = { 0 };

    AxisNorm = HMM_SquareRootF(HMM_DotVec3(Axis, Axis));
    SineOfRotation = HMM_SinF(AngleOfRotation / 2.0f);
    RotatedVector = HMM_MultiplyVec3f(Axis, SineOfRotation);

    Result.W = HMM_CosF(AngleOfRotation / 2.0f);
    Result.XYZ = HMM_DivideVec3f(RotatedVector, AxisNorm);

    return(Result);
}

HINLINE bool
HMM_CompareQuaternion(hmm_quaternion q1, hmm_quaternion q2)
{
    return (q1.X == q2.X && q1.Y == q2.Y && q1.Z == q2.Z && q1.W == q2.W);
}

#ifdef HANDMADE_MATH_CPP_MODE

HINLINE float
HMM_Length(hmm_vec2 A)
{
    float Result = 0.0f;

    Result = HMM_LengthVec2(A);

    return(Result);
}

HINLINE float
HMM_Length(hmm_vec3 A)
{
    float Result = 0.0f;

    Result = HMM_LengthVec3(A);

    return(Result);
}

HINLINE float
HMM_Length(hmm_vec4 A)
{
    float Result = 0.0f;

    Result = HMM_LengthVec4(A);

    return(Result);
}

HINLINE float
HMM_LengthSquared(hmm_vec2 A)
{
    float Result = 0.0f;

    Result = HMM_LengthSquaredVec2(A);

    return(Result);
}

HINLINE float
HMM_LengthSquared(hmm_vec3 A)
{
    float Result = 0.0f;

    Result = HMM_LengthSquaredVec3(A);

    return(Result);
}

HINLINE float
HMM_LengthSquared(hmm_vec4 A)
{
    float Result = 0.0f;

    Result = HMM_LengthSquaredVec4(A);

    return(Result);
}

HINLINE hmm_vec2
HMM_Normalize(hmm_vec2 A)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_NormalizeVec2(A);

    return(Result);
}

HINLINE hmm_vec3
HMM_Normalize(hmm_vec3 A)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_NormalizeVec3(A);

    return(Result);
}

HINLINE hmm_vec4
HMM_Normalize(hmm_vec4 A)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_NormalizeVec4(A);

    return(Result);
}

HINLINE hmm_quaternion
HMM_Normalize(hmm_quaternion A)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_NormalizeQuaternion(A);

    return(Result);
}

HINLINE float
HMM_Dot(hmm_vec2 VecOne, hmm_vec2 VecTwo)
{
    float Result = 0;

    Result = HMM_DotVec2(VecOne, VecTwo);

    return(Result);
}

HINLINE float
HMM_Dot(hmm_vec3 VecOne, hmm_vec3 VecTwo)
{
    float Result = 0;

    Result = HMM_DotVec3(VecOne, VecTwo);

    return(Result);
}

HINLINE float
HMM_Dot(hmm_vec4 VecOne, hmm_vec4 VecTwo)
{
    float Result = 0;

    Result = HMM_DotVec4(VecOne, VecTwo);

    return(Result);
}

HINLINE float
HMM_Dot(hmm_quaternion QuatOne, hmm_quaternion QuatTwo)
{
    float Result = 0;

    Result = HMM_DotQuaternion(QuatOne, QuatTwo);

    return(Result);
}

HINLINE hmm_vec2
HMM_Add(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_AddVec2(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Add(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_AddVec3(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Add(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_AddVec4(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Add(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_AddMat4(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
HMM_Add(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_AddQuaternion(Left, Right);
    return(Result);
}

HINLINE hmm_vec2
HMM_Subtract(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_SubtractVec2(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Subtract(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_SubtractVec3(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Subtract(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_SubtractVec4(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Subtract(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_SubtractMat4(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
HMM_Subtract(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_SubtractQuaternion(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
HMM_Multiply(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_MultiplyVec2(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
HMM_Multiply(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_MultiplyVec2f(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Multiply(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_MultiplyVec3(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Multiply(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_MultiplyVec3f(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Multiply(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_MultiplyVec4(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Multiply(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_MultiplyVec4f(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Multiply(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_MultiplyMat4(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Multiply(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_MultiplyMat4f(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Multiply(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_MultiplyMat4ByVec4(Matrix, Vector);
    return (Result);
}

HINLINE hmm_quaternion
HMM_Multiply(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_MultiplyQuaternion(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
HMM_Multiply(hmm_quaternion Left, float Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_MultiplyQuaternionF(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
HMM_Multiply(float Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_MultiplyQuaternionF(Right, Left);
    return (Result);
}

HINLINE hmm_vec2
HMM_Divide(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_DivideVec2(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
HMM_Divide(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_DivideVec2f(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Divide(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_DivideVec3(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
HMM_Divide(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_DivideVec3f(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Divide(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_DivideVec4(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
HMM_Divide(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_DivideVec4f(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
HMM_Divide(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_DivideMat4f(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
HMM_Divide(hmm_quaternion Left, float Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_DivideQuaternionF(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator+(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator+(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator+(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
operator+(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
operator+(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_Add(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator-(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator-(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator-(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
operator-(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
operator-(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_Subtract(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator*(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator*(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator*(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_Multiply(Left, Right);

    return (Result);
}

HINLINE hmm_vec2
operator*(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator*(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator*(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
operator*(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator*(float Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_vec3
operator*(float Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_vec4
operator*(float Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_mat4
operator*(float Left, hmm_mat4 Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_mat4
operator*(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator*(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_Multiply(Matrix, Vector);
    return (Result);
}

HINLINE hmm_quaternion
operator*(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
operator*(hmm_quaternion Left, float Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_Multiply(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
operator*(float Left, hmm_quaternion Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_Multiply(Right, Left);
    return (Result);
}

HINLINE hmm_vec2
operator/(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator/(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_Divide(Left, Right);

    return (Result);
}

HINLINE hmm_vec4
operator/(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec2
operator/(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = { 0 };

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec3
operator/(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = { 0 };

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec4
operator/(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = { 0 };

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_mat4
operator/(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = { 0 };

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_quaternion
operator/(hmm_quaternion Left, float Right)
{
    hmm_quaternion Result = { 0 };

    Result = HMM_Divide(Left, Right);
    return (Result);
}

HINLINE hmm_vec2 &
operator+=(hmm_vec2 &Left, hmm_vec2 Right)
{
    return (Left = Left + Right);
}

HINLINE hmm_vec3 &
operator+=(hmm_vec3 &Left, hmm_vec3 Right)
{
    return (Left = Left + Right);
}

HINLINE hmm_vec4 &
operator+=(hmm_vec4 &Left, hmm_vec4 Right)
{
    return (Left = Left + Right);
}

HINLINE hmm_mat4 &
operator+=(hmm_mat4 &Left, hmm_mat4 Right)
{
    return (Left = Left + Right);
}

HINLINE hmm_quaternion &
operator+=(hmm_quaternion &Left, hmm_quaternion Right)
{
    return (Left = Left + Right);
}

HINLINE hmm_vec2 &
operator-=(hmm_vec2 &Left, hmm_vec2 Right)
{
    return (Left = Left - Right);
}

HINLINE hmm_vec3 &
operator-=(hmm_vec3 &Left, hmm_vec3 Right)
{
    return (Left = Left - Right);
}

HINLINE hmm_vec4 &
operator-=(hmm_vec4 &Left, hmm_vec4 Right)
{
    return (Left = Left - Right);
}

HINLINE hmm_mat4 &
operator-=(hmm_mat4 &Left, hmm_mat4 Right)
{
    return (Left = Left - Right);
}

HINLINE hmm_quaternion &
operator-=(hmm_quaternion &Left, hmm_quaternion Right)
{
    return (Left = Left - Right);
}

HINLINE hmm_vec2 &
operator/=(hmm_vec2 &Left, hmm_vec2 Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec3 &
operator/=(hmm_vec3 &Left, hmm_vec3 Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec4 &
operator/=(hmm_vec4 &Left, hmm_vec4 Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec2 &
operator/=(hmm_vec2 &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec3 &
operator/=(hmm_vec3 &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec4 &
operator/=(hmm_vec4 &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_mat4 &
operator/=(hmm_mat4 &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_quaternion &
operator/=(hmm_quaternion &Left, float Right)
{
    return (Left = Left / Right);
}

HINLINE hmm_vec2 &
operator*=(hmm_vec2 &Left, hmm_vec2 Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_vec3 &
operator*=(hmm_vec3 &Left, hmm_vec3 Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_vec4 &
operator*=(hmm_vec4 &Left, hmm_vec4 Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_vec2 &
operator*=(hmm_vec2 &Left, float Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_vec3 &
operator*=(hmm_vec3 &Left, float Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_vec4 &
operator*=(hmm_vec4 &Left, float Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_mat4 &
operator*=(hmm_mat4 &Left, float Right)
{
    return (Left = Left * Right);
}

HINLINE hmm_quaternion &
operator*=(hmm_quaternion &Left, float Right)
{
    return (Left = Left * Right);
}

#endif /* HANDMADE_MATH_CPP_MODE */
