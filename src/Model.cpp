#include <iostream>
#include <filesystem>
#include <tiny_obj_loader.h>

#include "Model.hpp"
#include "Mesh.hpp"
#include "Vertex.hpp"
#include "Window.hpp"

Model::Model(std::string path) : Node() {
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig config;
    config.triangulate = true;

    if (!reader.ParseFromFile(path, config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader Error: " << reader.Error() << std::endl;
        }

        return;
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader Warning: " << reader.Warning() << std::endl;
    }

    tinyobj::attrib_t attrib = reader.GetAttrib();
    std::vector<tinyobj::shape_t> shapes = reader.GetShapes();
    std::vector<tinyobj::material_t> materials = reader.GetMaterials();

    for (size_t i = 0; i < shapes.size(); i++) {
	tinyobj::mesh_t mesh = shapes[i].mesh;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	if (mesh.material_ids.empty() || mesh.material_ids[0] < 0) continue;

	int matId = mesh.material_ids[0];
        if (matId >= materials.size()) continue;

	tinyobj::material_t mat = materials[matId];
	std::filesystem::path modelDir = std::filesystem::path(path).parent_path();
	std::string fullTexPath = (modelDir / mat.diffuse_texname).string();

	for (auto idx : mesh.indices) {
	    Vertex vert;

	    vert.position.x = attrib.vertices[3 * idx.vertex_index + 0];
	    vert.position.y = attrib.vertices[3 * idx.vertex_index + 1];
	    vert.position.z = attrib.vertices[3 * idx.vertex_index + 2];

	    if (idx.normal_index >= 0) {
		vert.normal.x = attrib.normals[3 * idx.normal_index + 0];
		vert.normal.y = attrib.normals[3 * idx.normal_index + 1];
		vert.normal.z = attrib.normals[3 * idx.normal_index + 2];
	    } else {
	    }

	    if (idx.texcoord_index >= 0) {
		vert.texCoords.x = attrib.texcoords[2 * idx.texcoord_index + 0];
		vert.texCoords.y = attrib.texcoords[2 * idx.texcoord_index + 1];
	    } else {
	    }

	    vertices.push_back(vert);
	    indices.push_back(static_cast<unsigned int>(vertices.size() - 1));
	}

	std::cout << fullTexPath << "\n";
	new Mesh(this, vertices, indices, fullTexPath);
    }

    setParent(Window::parent);
}
