class Texture
{
public:
   Texture(GLenum TextureTarget, const std::string& FileName);

   bool Load();

   void Bind(GLenum TextureUnit);
}; 
