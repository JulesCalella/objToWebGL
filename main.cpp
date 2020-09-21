#include <iostream>
#include <fstream>
#include <string>

#define MAX_SIZE 10000

//using namespace std;

int main(int argc, char **argv)
{
    if(argc < 3) {
        std::cout << "Too few parameters passed." << std::endl;
        return -1;
    }

    int ret, i, retInt, retTemp, repeat, currElem, sign, numVert;
    float retFloat;
    char retChar;
    std::string fileLine;
    std::string result;

    // Arrays
    float vertices[MAX_SIZE];   // Values collected directly from file
    int eVert = 0;
    float textures[MAX_SIZE];
    int eText = 0;
    float normals[MAX_SIZE];
    int eNorm = 0;
    int faceVerts[MAX_SIZE];    // Values indicating indices
    int eFaceVert = 0;
    int faceTexts[MAX_SIZE];
    int eFaceText = 0;
    int faceNorms[MAX_SIZE];
    int eFaceNorm = 0;
    float output[MAX_SIZE];     // The vertices selected by the face
    int eOutput = 0;
    int faceNumVert[MAX_SIZE];  // Faces have 3 or 4 vertices. This will show how many faces will need to be interpreted when writing to the file
    int eFaceNumVert = 0;


    // Open the file passed as a parameter
    std::ifstream objFile (argv[1]);
    if(!objFile.is_open()) {
            std::cout << "Could not open file " << argv[1] << std::endl;
            return -1;
    }

    // Read file. Stop at EOF (== 0)
    while(std::getline(objFile, fileLine)){
        std::cout << fileLine << std::endl;

        // VERTICES
        if((fileLine[0] == 'v') && (fileLine[1] == ' ')){
            // If vertices found (v), store in vertices array
            i = 2;
            for(repeat=0; repeat<3; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                vertices[eVert] = (retInt + retFloat) * sign;
                std::cout << vertices[eVert] << std::endl;
                eVert++;

                i++;
            }

        }
        // TEXTURES
        else if((fileLine[0] == 'v') && (fileLine[1] == 't')){
            // If vertices found (v), store in vertices array
            i = 3;
            for(repeat=0; repeat<2; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                textures[eText] = (retInt + retFloat) * sign;
                std::cout << textures[eText] << std::endl;
                eText++;

                i++;
            }

        }
        // NORMALS
        else if((fileLine[0] == 'v') && (fileLine[1] == 'n')){
            // If vertices found (v), store in vertices array
            i = 3;
            for(repeat=0; repeat<3; repeat++) {
                retInt = 0;
                retTemp = 0;
                retFloat = 0.0f;
                // Get whole numbers
                sign = 1;
                if(fileLine[i] == '-') {
                    sign = -1;
                    i++;
                }
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                // Check for decimal
                if(fileLine[i] == '.') {
                    i++;
                    float mult = 0.1;
                    while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                        retTemp = fileLine[i] - '0';
                        retFloat += (retTemp * mult);
                        i++;
                        mult *= 0.1;
                    }
                }

                // Save read value to the array
                normals[eNorm] = (retInt + retFloat) * sign;
                std::cout << normals[eNorm] << std::endl;
                eNorm++;

                i++;
            }

        }
        // If faces found (f), store in faceVer
        else if((fileLine[0] == 'f') && (fileLine[1] == ' ')) {
            // The first number of each group is the vert
            i = 2;
            numVert = 0;
            while(fileLine[i] != 0) {
                // Vertex
                retInt = 0;
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceVerts[eFaceVert] = retInt;
                eFaceVert++;

                // Textures
                retInt = 0;
                i++;
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceTexts[eFaceText] = retInt;
                eFaceText++;

                // Normals
                retInt = 0;
                i++;
                while((fileLine[i] >= '0') && (fileLine[i] <= '9')) {
                    retChar = fileLine[i];
                    i++;
                    retInt *= 10;
                    retInt += (retChar - '0');
                }
                faceNorms[eFaceNorm] = retInt;
                eFaceNorm++;

                if(fileLine[i] == ' ') i++;

                numVert++;
            }
            faceNumVert[eFaceNumVert] = numVert;
            eFaceNumVert++;
            std::cout << "Num Verts in face: " << numVert << std::endl;
        }
    }

    // Close current file
    objFile.close();

    // Create output vertices
    // Each face is 4 points
    // Every texture is tied to a vertex
    // [f] a b c d -> abc + cda
    // For each texture, copy data from vertices[] in new output

    // Create output file
    std::ofstream outFile (argv[2]);
    if(!outFile.is_open()) {
            std::cout << "Could not create file " << argv[2] << std::endl;
            return -1;
    }

    //
    // Write Textures to file
    //
    outFile << "const texVerts = [" << std::endl;
    int numPrinted = 0;
    for(i=0; i<eText; i++) {
        outFile << "\t" << textures[i] << ", ";
        numPrinted++;
        if(numPrinted >= 2) {
            numPrinted = 0;
            outFile << std::endl;
        }
    }
    outFile << "];\n\n" << std::endl;

    //
    // Write vertices to file
    //
    outFile << "const vertices = [" << std::endl;
    int j;
    for(i=1; i<=eText; i++) {
        // Find the textures in numerical order
        for(j=0; j<eFaceText; j++) {
            // Find which faceText links to text[i]
            if(faceTexts[j] == i) {
                // 1:1 with faceText and faceVerts means they are linked
                // Find which vertex is referenced by this element
                // Subtract by 1 to account for indexing from 0
                j = (faceVerts[j] - 1) * 3;
                outFile << "\t" << vertices[j] << ", " << vertices[j+1] << ", " << vertices[j+2] << "," << std::endl;
                break;
            }
        }
    }
    outFile << "];\n\n" << std::endl;

    //
    // Write indices to file
    //
    outFile << "const indices = [" << std::endl;
    j = 0;
    for(i=0; i<eFaceText; ) {
        outFile << faceTexts[i]-1 <<", "<< faceTexts[i+1]-1 <<", "<< faceTexts[i+2]-1 << ","<< std::endl;
        if(faceNumVert[j] == 4) {
            outFile << faceTexts[i+2]-1 <<", "<< faceTexts[i+3]-1 <<", "<< faceTexts[i]-1 << ","<< std::endl;
            i += 4;
        } else {
            i += 3;
        }

        j++;
    }
    outFile << "];\n\n" << std::endl;

    //
    // Write normals to file
    //

    // Close file
    outFile.close();

    return 0;
}
