#ifndef RF_OPENGLMODEL_HPP
#define RF_OPENGLMODEL_HPP

namespace RadonFramework::Drawing {

class OpenGLModel
{
public:
    void Generate(RF_Type::Float32* Vertices, RF_Type::Size VertexCount, 
                  RF_Type::Size ElementsPerVertex);
    void Generate(RF_Type::Float32* Vertices, RF_Type::Float32* Colors, 
        RF_Type::Size VertexCount, RF_Type::Size ElementsPerVertex);
    void Bind();
    void Unbind();
    void Draw();
    void Update(RF_Type::Float32* Vertices, RF_Type::Size VertexCount,
                RF_Type::Size ElementsPerVertex);
    void Update(RF_Type::Float32* Vertices, RF_Type::Float32* Colors,
        RF_Type::Size VertexCount, RF_Type::Size ElementsPerVertex);
    RF_Type::UInt32 Hash;
private:
    RF_Type::UInt32 m_VBOs[3];
    RF_Type::UInt32 m_VAO;
    RF_Type::Size m_VertexCount;
};

}

#endif // ! RE_OPENGLMODEL_HPP