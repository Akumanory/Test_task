#include <glm/glm.hpp>
#include <iostream>

//
// Calculate smooth (average) per-vertex normals
//
// [out] normals - output per-vertex normals
// [in] verts - input per-vertex positions
// [in] faces - triangles (triplets of vertex indices)
// [in] nverts - total number of vertices (# of elements in verts and normals arrays)
// [in] nfaces - total number of faces (# of elements in faces array)
//

void calc_mesh_normals(glm::vec3* normals, const glm::vec3* verts, const int* faces, int nverts, int nfaces)
{
    std::cout << "nverts: " << nverts << std::endl;
    std::cout << "nfaces: " << nfaces << std::endl;

    // normal for triangle by verts
    glm::vec3 normals_for_trianlge[nfaces / 3];

    // std::cout << std::endl;
    // std::cout << "normals_for_trianlge: " << nfaces << std::endl;

    for (auto i = 0; i < nfaces; i = i + 3)
    {

        // face first index
        auto A = faces[i]; // A
        // face second index
        auto B = faces[i + 1]; // B
        // face third index
        auto C = faces[i + 2]; // C

        auto B_A = verts[B] - verts[A];
        auto C_A = verts[C] - verts[A];

        normals_for_trianlge[i / 3] = glm::cross(B_A, C_A);
        normals_for_trianlge[i / 3] = glm::normalize(normals_for_trianlge[i / 3]);

        // std::cout << "index: " << i / 3 << std::endl;
        // std::cout << "nx: " << normals_for_trianlge[i / 3].x << std::endl;
        // std::cout << "ny: " << normals_for_trianlge[i / 3].y << std::endl;
        // std::cout << "nz: " << normals_for_trianlge[i / 3].z << std::endl;
        // std::cout << std::endl;

    }

    for (auto i = 0; i < nverts; i++)
    {
        float count = 0.0f;
        for (auto j = 0; j < nfaces; j = j + 3)
        {
            for (auto k = 0; k < 3; k++)
            {
                if(i == faces[j + k])
                {
                    normals[i] += normals_for_trianlge[j / 3];
                    count++;
                    break;
                }
            }
        }
        normals[i] = glm::normalize(normals[i] / count);
    }
}



int main()
{

    glm::vec3 verts[] = {
        glm::vec3(-1.0, -1.0, -1.0), //FRONT Bottom Left   - [0]
        glm::vec3(-1.0,  1.0, -1.0), //FRONT Top Left      - [1]
        glm::vec3( 1.0,  1.0, -1.0), //FRONT Top Right     - [2]
        glm::vec3( 1.0, -1.0, -1.0), //FRONT Bottom Right  - [3]
        glm::vec3(-1.0, -1.0,  1.0), //BACK Bottom Left    - [4]
        glm::vec3(-1.0,  1.0,  1.0), //BACK Top Left       - [5]
        glm::vec3( 1.0,  1.0,  1.0), //BACK Top Right      - [6]
        glm::vec3( 1.0, -1.0,  1.0), //BACK Bottom Right   - [7]
    };

    int faces[] = {
        0, 1, 2, //FRONT
		0, 2, 3, //FRONT
		4, 7, 6, //BACK
		4, 6, 5, //BACK
		3, 2, 6, //RIGHT SIDE
		3, 6, 7, //RIGHT SIDE
		4, 5, 1, //LEFT SIDE
		4, 1, 0, //LEFT SIDE
		1, 5, 6, //TOP
		1, 6, 2, //TOP
		0, 3, 7, //BOTTOM
		0, 7, 4  //BOTTOM
    };

    glm::vec3 normals[] = {
        glm::vec3(), //FRONT Bottom Left   - [0]
        glm::vec3(), //FRONT Top Left      - [1]
        glm::vec3(), //FRONT Top Right     - [2]
        glm::vec3(), //FRONT Bottom Right  - [3]
        glm::vec3(), //BACK Bottom Left    - [4]
        glm::vec3(), //BACK Top Left       - [5]
        glm::vec3(), //BACK Top Right      - [6]
        glm::vec3(), //BACK Bottom Right   - [7]
    };

    calc_mesh_normals(normals, verts, faces, sizeof(verts) / sizeof(verts[0]), sizeof(faces) / sizeof(faces[0]));

    for (auto i = 0; i < (sizeof(normals) / sizeof(normals[0])); i++)
    {
        std::cout << "index: " << i << std::endl;
        std::cout << "nx: " << normals[i].x << std::endl;
        std::cout << "ny: " << normals[i].y << std::endl;
        std::cout << "nz: " << normals[i].z << std::endl;
        std::cout << std::endl;
    }

    return 0;
}