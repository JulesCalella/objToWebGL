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
    int numVertices = 0;
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
            numVertices++;

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
    // Update vertices and faceVerts
    //
    // Iterate through every faceTexts element
    int ftCurrElem, ftCurrValue, ftElemMax, ftDiffValue;
    int fvCurrElem, fvCurrValue, fvElemMax, fvDiffValue;
    int diffElem, verticesPrevElem, verticesNewElem;
    for(ftCurrElem=0; ftCurrElem<eFaceText; ftCurrElem++) {
        // Record the current value of the faceTexts array
        ftCurrValue = faceTexts[ftCurrElem];
        // Record the current associated value for faceVerts
        fvCurrValue = faceVerts[ftCurrElem];
        // Search through remaining faceVerts value for fvCurrValue
        for(fvCurrElem=ftCurrElem+1; fvCurrElem<eFaceText; fvCurrElem++) {
            // If ==fvCurrValue but !=ftCurrValue -> Mismatched pair: Update the vertex
            if((faceVerts[fvCurrElem] == fvCurrValue) && (faceTexts[fvCurrElem] != ftCurrValue)) {
                // Mismatch found. Now we have to run through the remaining values (including this one)
                // looking for this exact pair and update the vertex value.
                ftDiffValue = faceTexts[fvCurrElem];
                fvDiffValue = ++numVertices;
                for(diffElem=fvCurrElem; diffElem<eFaceText; diffElem++) {
                    // If match found, update the vertex to fvDiffValue
                    // Here we are only changing faceVerts of the current pair
                    if((faceTexts[diffElem] == ftDiffValue) && (faceVerts[diffElem] == fvCurrValue)) {
                        faceVerts[diffElem] = fvDiffValue;
                    }
                }

                // Copy the actual vertex data in vertices
                verticesPrevElem = (fvCurrValue - 1) * 3;
                verticesNewElem = (fvDiffValue - 1) * 3;
                vertices[verticesNewElem] = vertices[verticesPrevElem];
                vertices[verticesNewElem+1] = vertices[verticesPrevElem+1];
                vertices[verticesNewElem+2] = vertices[verticesPrevElem+2];
                eVert+=3;
            }
        }
    }

    //
    // Write vertices to file
    //
    outFile << "function createVert() {\n\tconst vertices = [" << std::endl;
    int j;
    for(i=0; i<eVert; i+=3) {
        outFile << "\t\t" << vertices[i] << ", " << vertices[i+1] << ", " << vertices[i+2] << "," << std::endl;
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn vertices;\n}\n" << std::endl;


    //
    // Write Textures to file
    //
    outFile << "function createText() {\n\tconst texVerts = [" << std::endl;
    int numPrinted = 0;
    int tIndex;
    for(j=1; j<=numVertices; j++) {
        // Iterate through faceVerts, looking for values in numerical order i.e. faceVerts[i]==j 1<=j<=eFaceVert
        for(i=0; i<eFaceVert; i++) {
            if(faceVerts[i] == j) {
                tIndex = (faceTexts[i] - 1) * 2;
                outFile << "\t\t" << textures[tIndex] << ", " << textures[tIndex+1] << "," << std::endl;
                break;
            }
        }
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn texVerts;\n}\n" << std::endl;


    //
    // Write indices to file
    //
    outFile << "function createIndi() {\n\tconst indices = [" << std::endl;
    j = 0;
    for(i=0; i<eFaceVert; ) {
        outFile << "\t\t" << faceVerts[i]-1 <<", "<< faceVerts[i+1]-1 <<", "<< faceVerts[i+2]-1 << ","<< std::endl;
        if(faceNumVert[j] == 4) {
            outFile << "\t\t" << faceVerts[i+2]-1 <<", "<< faceVerts[i+3]-1 <<", "<< faceVerts[i]-1 << ","<< std::endl;
            i += 4;
        } else {
            i += 3;
        }

        j++;
    }
    outFile << "\t];\n" << std::endl;
    outFile << "\treturn indices;\n}\n" << std::endl;

    //
    // Write normals to file
    //


    // Close file
    outFile.close();

    return 0;
}
