#ifndef RF_OPENGLSHADER_HPP
#define RF_OPENGLSHADER_HPP

namespace RadonFramework::Drawing {

class OpenGLShader
{
public:
    void Generate();
    void Bind();
    void Unbind();    
private:
    RF_Type::UInt32 shader_programme = 0;
};

}

#endif //!RF_OPENGLSHADER_HPP