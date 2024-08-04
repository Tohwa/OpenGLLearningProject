#include "GameObject.h"

// Constructor to initialize the GameObject with a name and position.
// Also initializes the transform and mesh components.
GameObject::GameObject(std::string _name, glm::vec3 _position) : transform(_position), mesh(transform)
{
    m_name = _name; // Set the name of the GameObject
    transform.Initialize(*this); // Initialize the transform component
    AddComponent(&transform); // Add the transform component to the list of components
}

// Initialize the GameObject with textures and shader paths.
// Configures the shader, light, material, and mesh components.
void GameObject::Initialize(std::vector<std::string> _textures, const char* _vertPath, const char* _fragPath)
{
    // Define shader file suffixes
    const char* vertexEnding = "Vertex.glsl";
    const char* fragEnding = "Fragment.glsl";

    // Construct the full paths for the vertex and fragment shaders
    std::string vertexPath = std::string(_vertPath) + vertexEnding;
    std::string fragmentPath = std::string(_fragPath) + fragEnding;

    // Initialize the shader with the constructed paths
    shader = SShader(vertexPath.c_str(), fragmentPath.c_str());
    m_shader = &shader; // Set the shader for this GameObject

    // Initialize the light component with the shader
    Light light{};
    light.Initialize(&shader);

    // Initialize the material component with the shader and textures
    material.Initialize(*this);
    material.InitShader(&shader, _textures);

    // Initialize the mesh component
    mesh.Initialize(*this);

    // Add material and mesh components to the list of components
    AddComponent(&material);
    AddComponent(&mesh);
}

// Update the GameObject's components
void GameObject::Update()
{
    transform.Update(); // Update the transform component
    material.Update(); // Update the material component
    mesh.Update(); // Update the mesh component
}

// Perform any additional updates after the main update
void GameObject::LateUpdate()
{
    // No specific late update functionality for now
}

// Draw the GameObject using the provided camera
void GameObject::Draw(Camera& _camera)
{
    transform.Draw(_camera); // Draw the transform component
    material.Draw(_camera); // Draw the material component
    mesh.Draw(_camera); // Draw the mesh component
}

// Add a component to the GameObject's list of components
void GameObject::AddComponent(IComponent* _component)
{
    if (!_component) return; // Ignore null components
    m_Components.push_back(_component); // Add the component to the list
}

// Remove a component from the GameObject's list of components
void GameObject::DeleteComponent(IComponent* _component)
{
    if (!_component) return; // Ignore null components

    // Search for the component and remove it from the list
    for (int i = 0; i < m_Components.size(); i++) {
        if (m_Components[i] == _component) {
            m_Components.erase(m_Components.begin() + i);
            break;
        }
    }
}

// Retrieve the shader associated with the GameObject
SShader GameObject::GetShaderData()
{
    return *m_shader; // Return the shader object
}

// Placeholder function for retrieving render data (not implemented)
void GameObject::GetRenderData()
{
    // Not yet implemented
}

// Finalize and clean up any resources used by the GameObject
void GameObject::Finalize()
{
    // No specific finalization functionality for now
}