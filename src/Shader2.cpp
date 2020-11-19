#include "../include/Shader2.hpp"

Shader2::Shader2(const char *vertexShader, const char *fragmentShader, const char *geometryShader, const bool &fromFile)
    : _programId(0), _vertexId(0), _fragmentId(0), _geometryId(0), _compiled(false)
{

    std::string vsStr;
    std::string fsStr;
    std::string gsStr;

    if (fromFile)
    {
        vsStr = parseFile(vertexShader);
        fsStr = parseFile(fragmentShader);
        if (geometryShader != nullptr)
        {
            gsStr = parseFile(geometryShader);
        }
        else
        {
            gsStr = "";
        }
    }
    else
    {
        vsStr = vertexShader;
        fsStr = fragmentShader;
        if (geometryShader != nullptr)
        {
            gsStr = geometryShader;
        }
        else
        {
            gsStr = "";
        }
    }

    _programId = glCreateProgram();

    // compile shaders
    _vertexId = compileShader(GL_VERTEX_SHADER, vsStr);
    _fragmentId = compileShader(GL_FRAGMENT_SHADER, fsStr);

    if (geometryShader != nullptr)
    {
        _geometryId = compileShader(GL_GEOMETRY_SHADER, gsStr);
    }

    AttachShaderId("vertex", _vertexId);
    AttachShaderId("fragment", _fragmentId);
    if (geometryShader != nullptr)
    {
        AttachShaderId("geometry", _geometryId);
    }

    glLinkProgram(_programId);

    int linkResult;
    glGetProgramiv(_programId, GL_LINK_STATUS, &linkResult);
    if (linkResult == GL_FALSE)
    {
        glDeleteProgram(_programId);
        std::cerr << "Shader creation aborded (linking doesn't work)" << std::endl;
    }
    else
    {
        glValidateProgram(_programId);
        _compiled = true;
    }

    glDeleteShader(_vertexId);
    glDeleteShader(_fragmentId);
    if (geometryShader != nullptr)
        glDeleteShader(_geometryId);
}

Shader2::~Shader2()
{
    if (_programId != 0)
        glDeleteProgram(_programId);
}

void Shader2::AttachShaderId(const char *shaderName, const GLuint id)
{
    if (id != 0)
    {
        glAttachShader(_programId, id);
        std::cout << shaderName << " shader attached " << std::endl;
    }
    else
    {
        std::cout << "[Shader] creation aborded (" << shaderName << " shader not compiled)" << std::endl;
        assert(false);
    }
}

GLuint Shader2::compileShader(const GLenum &shaderType, const std::string &shaderStr)
{

    GLuint shaderId = glCreateShader(shaderType);

    if (shaderId)
    {

        const char *shaderCode = shaderStr.c_str();
        glShaderSource(shaderId, 1, &shaderCode, nullptr);
        glCompileShader(shaderId);

        int compileResult;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);
        if (compileResult == GL_FALSE)
        {

            int infosLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infosLength);
            std::vector<char> message(infosLength);
            glGetShaderInfoLog(shaderId, infosLength, &infosLength, &message[0]);
            std::cout << "[Shader] error during compiling shader (" << shaderTypeStr(shaderType) << ") :" << std::endl
                      << &message[0] << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "[Shader] Failed to assign new shader id (" << shaderTypeStr(shaderType) << " shader)" << std::endl;
    }
    return shaderId;
}

std::string Shader2::parseFile(const char *filepath)
{

    std::string shaderStr;
    std::ifstream file(filepath, std::ios::in);

    if (!file.is_open())
    {
        std::cerr << "[Shader] Failed to open file : " + *filepath << std::endl;
    }

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    shaderStr = stream.str();

    return shaderStr;
}

bool Shader2::bind() const
{
    if (_compiled)
    {
        glUseProgram(_programId);
    }
    return _compiled;
};

std::string Shader2::shaderTypeStr(const GLenum &shaderType)
{
    switch (shaderType)
    {
    case GL_FRAGMENT_SHADER:
        return "GL_FRAGMENT_SHADER";

    case GL_GEOMETRY_SHADER:
        return "GL_GEOMETRY_SHADER";

    case GL_COMPUTE_SHADER:
        return "GL_COMPUTE_SHADER";

    case GL_VERTEX_SHADER:
        return "GL_VERTEX_SHADER";

    case GL_TESS_CONTROL_SHADER:
        return "GL_TESS_CONTROL_SHADER";

    case GL_TESS_EVALUATION_SHADER:
        return "GL_TESS_EVALUATION_SHADER";

    default:
        assert(!"unknown shader type");
        return nullptr;
    }
}

GLint Shader2::getUniform(const std::string &uniformName)
{
    if (_uniformLocationCache.find(uniformName) != _uniformLocationCache.end())
    {
        return _uniformLocationCache[uniformName];
    }

    GLint location = glGetUniformLocation(_programId, uniformName.c_str());

    if (location == -1)
    {
        std::cerr << "[Shader] uniform \"" << uniformName << "\" doesn't exist" << std::endl;
    }

    _uniformLocationCache[uniformName] = location;
    return location;
}

void Shader2::setInt(const std::string &uniformName, int v)
{
    glUniform1i(getUniform(uniformName), v);
}

void Shader2::setFloat(const std::string &uniformName, float v)
{
    glUniform1f(getUniform(uniformName), v);
}

void Shader2::setVec2f(const std::string &uniformName, const glm::vec2 &v)
{
    glUniform2f(getUniform(uniformName), v.x, v.y);
}

void Shader2::setVec2f(const std::string &uniformName, const float &x, const float &y)
{
    glUniform2f(getUniform(uniformName), x, y);
}

void Shader2::setVec3f(const std::string &uniformName, const glm::vec3 &v)
{
    glUniform3f(getUniform(uniformName), v.x, v.y, v.z);
}

void Shader2::setVec3f(const std::string &uniformName, const float &x, const float &y, const float &z)
{
    glUniform3f(getUniform(uniformName), x, y, z);
}

void Shader2::setVec4f(const std::string &uniformName, const glm::vec4 &v)
{
    glUniform4f(getUniform(uniformName), v.x, v.y, v.z, v.w);
}

void Shader2::setVec4f(const std::string &uniformName, const float &x, const float &y, const float &z, const float &w)
{
    glUniform4f(getUniform(uniformName), x, y, z, w);
}

void Shader2::setMat3(const std::string &uniformName, const glm::mat3 &m)
{
    glUniformMatrix3fv(getUniform(uniformName), 1, GL_FALSE, &m[0][0]);
}

void Shader2::setMat4(const std::string &uniformName, const glm::mat4 &m)
{
    glUniformMatrix4fv(getUniform(uniformName), 1, GL_FALSE, &m[0][0]);
}