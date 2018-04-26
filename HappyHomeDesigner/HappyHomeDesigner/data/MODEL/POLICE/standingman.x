xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 535;
 -2.20000;37.81858;-2.20000;,
 2.20000;37.81858;-2.20000;,
 2.20000;33.41858;-2.20000;,
 -2.20000;33.41858;-2.20000;,
 2.20000;37.81858;-2.20000;,
 2.20000;37.81858;2.20000;,
 2.20000;33.41858;2.20000;,
 2.20000;33.41858;-2.20000;,
 2.20000;37.81858;2.20000;,
 -2.20000;37.81858;2.20000;,
 -2.20000;33.41858;2.20000;,
 2.20000;33.41858;2.20000;,
 -2.20000;37.81858;2.20000;,
 -2.20000;37.81858;-2.20000;,
 -2.20000;33.41858;-2.20000;,
 -2.20000;33.41858;2.20000;,
 2.20000;37.81858;-2.20000;,
 -2.20000;37.81858;-2.20000;,
 -2.20000;33.41858;-2.20000;,
 2.20000;33.41858;-2.20000;,
 -3.27500;32.13758;-2.90240;,
 3.27500;32.13758;-2.90240;,
 3.27500;25.58758;-2.90240;,
 -3.27500;25.58758;-2.90240;,
 3.27500;32.13758;-2.90240;,
 3.27500;32.13758;2.80354;,
 3.27500;25.58758;2.80354;,
 3.27500;25.58758;-2.90240;,
 3.27500;32.13758;2.80354;,
 -3.27500;32.13758;2.80354;,
 -3.27500;25.58758;2.80354;,
 3.27500;25.58758;2.80354;,
 -3.27500;32.13758;2.80354;,
 -3.27500;32.13758;-2.90240;,
 -3.27500;25.58758;-2.90240;,
 -3.27500;25.58758;2.80354;,
 3.27500;32.13758;-2.90240;,
 -3.27500;32.13758;-2.90240;,
 -3.27500;25.58758;-2.90240;,
 3.27500;25.58758;-2.90240;,
 -3.00000;25.02358;-2.39689;,
 3.00000;25.02358;-2.39689;,
 3.00000;21.89358;-2.39689;,
 -3.00000;21.89358;-2.39689;,
 3.00000;25.02358;-2.39689;,
 3.00000;25.02358;2.39689;,
 3.00000;21.89358;2.39689;,
 3.00000;21.89358;-2.39689;,
 3.00000;25.02358;2.39689;,
 -3.00000;25.02358;2.39689;,
 -3.00000;21.89358;2.39689;,
 3.00000;21.89358;2.39689;,
 -3.00000;25.02358;2.39689;,
 -3.00000;25.02358;-2.39689;,
 -3.00000;21.89358;-2.39689;,
 -3.00000;21.89358;2.39689;,
 3.00000;25.02358;-2.39689;,
 -3.00000;25.02358;-2.39689;,
 -3.00000;21.89358;-2.39689;,
 3.00000;21.89358;-2.39689;,
 -3.00000;21.55758;-2.39689;,
 3.00000;21.55758;-2.39689;,
 3.00000;18.42758;-2.39689;,
 -3.00000;18.42758;-2.39689;,
 3.00000;21.55758;-2.39689;,
 3.00000;21.55758;2.39689;,
 3.00000;18.42758;2.39689;,
 3.00000;18.42758;-2.39689;,
 3.00000;21.55758;2.39689;,
 -3.00000;21.55758;2.39689;,
 -3.00000;18.42758;2.39689;,
 3.00000;18.42758;2.39689;,
 -3.00000;21.55758;2.39689;,
 -3.00000;21.55758;-2.39689;,
 -3.00000;18.42758;-2.39689;,
 -3.00000;18.42758;2.39689;,
 3.00000;21.55758;-2.39689;,
 -3.00000;21.55758;-2.39689;,
 -3.00000;18.42758;-2.39689;,
 3.00000;18.42758;-2.39689;,
 0.49400;17.86858;-1.31000;,
 3.11400;17.86858;-1.31000;,
 3.11400;10.12858;-1.31000;,
 0.49400;10.12858;-1.31000;,
 3.11400;17.86858;-1.31000;,
 3.11400;17.86858;1.31000;,
 3.11400;10.12858;1.31000;,
 3.11400;10.12858;-1.31000;,
 3.11400;17.86858;1.31000;,
 0.49400;17.86858;1.31000;,
 0.49400;10.12858;1.31000;,
 3.11400;10.12858;1.31000;,
 0.49400;17.86858;1.31000;,
 0.49400;17.86858;-1.31000;,
 0.49400;10.12858;-1.31000;,
 0.49400;10.12858;1.31000;,
 3.11400;17.86858;-1.31000;,
 0.49400;17.86858;-1.31000;,
 0.49400;10.12858;-1.31000;,
 3.11400;10.12858;-1.31000;,
 0.49400;9.60458;-1.31000;,
 3.11400;9.60458;-1.31000;,
 3.11400;2.63458;-1.31000;,
 0.49400;2.63458;-1.31000;,
 3.11400;9.60458;-1.31000;,
 3.11400;9.60458;1.31000;,
 3.11400;2.63458;1.31000;,
 3.11400;2.63458;-1.31000;,
 3.11400;9.60458;1.31000;,
 0.49400;9.60458;1.31000;,
 0.49400;2.63458;1.31000;,
 3.11400;2.63458;1.31000;,
 0.49400;9.60458;1.31000;,
 0.49400;9.60458;-1.31000;,
 0.49400;2.63458;-1.31000;,
 0.49400;2.63458;1.31000;,
 3.11400;9.60458;-1.31000;,
 0.49400;9.60458;-1.31000;,
 0.49400;2.63458;-1.31000;,
 3.11400;2.63458;-1.31000;,
 0.49400;2.55058;-2.30300;,
 3.11400;2.55058;-2.30300;,
 3.11400;0.12058;-2.30300;,
 0.49400;0.12058;-2.30300;,
 3.11400;2.55058;-2.30300;,
 3.11400;2.55058;1.10700;,
 3.11400;0.12058;1.10700;,
 3.11400;0.12058;-2.30300;,
 3.11400;2.55058;1.10700;,
 0.49400;2.55058;1.10700;,
 0.49400;0.12058;1.10700;,
 3.11400;0.12058;1.10700;,
 0.49400;2.55058;1.10700;,
 0.49400;2.55058;-2.30300;,
 0.49400;0.12058;-2.30300;,
 0.49400;0.12058;1.10700;,
 3.11400;2.55058;-2.30300;,
 0.49400;2.55058;-2.30300;,
 0.49400;0.12058;-2.30300;,
 3.11400;0.12058;-2.30300;,
 0.88400;1.41158;-4.69500;,
 2.72400;1.41158;-4.69500;,
 2.72400;0.06158;-4.69500;,
 0.88400;0.06158;-4.69500;,
 2.72400;1.41158;-4.69500;,
 2.72400;1.41158;-2.77500;,
 2.72400;0.06158;-2.77500;,
 2.72400;0.06158;-4.69500;,
 2.72400;1.41158;-2.77500;,
 0.88400;1.41158;-2.77500;,
 0.88400;0.06158;-2.77500;,
 2.72400;0.06158;-2.77500;,
 0.88400;1.41158;-2.77500;,
 0.88400;1.41158;-4.69500;,
 0.88400;0.06158;-4.69500;,
 0.88400;0.06158;-2.77500;,
 2.72400;1.41158;-4.69500;,
 0.88400;1.41158;-4.69500;,
 0.88400;0.06158;-4.69500;,
 2.72400;0.06158;-4.69500;,
 3.45400;32.65058;-2.32500;,
 6.97400;32.65058;-2.32500;,
 6.97400;27.74058;-2.32500;,
 3.45400;27.74058;-2.32500;,
 6.97400;32.65058;-2.32500;,
 6.97400;32.65058;2.32500;,
 6.97400;27.74058;2.32500;,
 6.97400;27.74058;-2.32500;,
 6.97400;32.65058;2.32500;,
 3.45400;32.65058;2.32500;,
 3.45400;27.74058;2.32500;,
 6.97400;27.74058;2.32500;,
 3.45400;32.65058;2.32500;,
 3.45400;32.65058;-2.32500;,
 3.45400;27.74058;-2.32500;,
 3.45400;27.74058;2.32500;,
 6.97400;32.65058;-2.32500;,
 3.45400;32.65058;-2.32500;,
 3.45400;27.74058;-2.32500;,
 6.97400;27.74058;-2.32500;,
 4.05900;27.43458;-0.97000;,
 6.36900;27.43458;-0.97000;,
 6.36900;24.00458;-0.97000;,
 4.05900;24.00458;-0.97000;,
 6.36900;27.43458;-0.97000;,
 6.36900;27.43458;0.97000;,
 6.36900;24.00458;0.97000;,
 6.36900;24.00458;-0.97000;,
 6.36900;27.43458;0.97000;,
 4.05900;27.43458;0.97000;,
 4.05900;24.00458;0.97000;,
 6.36900;24.00458;0.97000;,
 4.05900;27.43458;0.97000;,
 4.05900;27.43458;-0.97000;,
 4.05900;24.00458;-0.97000;,
 4.05900;24.00458;0.97000;,
 6.36900;27.43458;-0.97000;,
 4.05900;27.43458;-0.97000;,
 4.05900;24.00458;-0.97000;,
 6.36900;24.00458;-0.97000;,
 4.05900;23.45258;-0.97000;,
 6.36900;23.45258;-0.97000;,
 6.36900;18.70258;-0.97000;,
 4.05900;18.70258;-0.97000;,
 6.36900;23.45258;-0.97000;,
 6.36900;23.45258;0.97000;,
 6.36900;18.70258;0.97000;,
 6.36900;18.70258;-0.97000;,
 6.36900;23.45258;0.97000;,
 4.05900;23.45258;0.97000;,
 4.05900;18.70258;0.97000;,
 6.36900;18.70258;0.97000;,
 4.05900;23.45258;0.97000;,
 4.05900;23.45258;-0.97000;,
 4.05900;18.70258;-0.97000;,
 4.05900;18.70258;0.97000;,
 6.36900;23.45258;-0.97000;,
 4.05900;23.45258;-0.97000;,
 4.05900;18.70258;-0.97000;,
 6.36900;18.70258;-0.97000;,
 3.86900;18.44458;-1.16000;,
 6.55900;18.44458;-1.16000;,
 6.55900;15.31458;-1.16000;,
 3.86900;15.31458;-1.16000;,
 6.55900;18.44458;-1.16000;,
 6.55900;18.44458;1.16000;,
 6.55900;15.31458;1.16000;,
 6.55900;15.31458;-1.16000;,
 6.55900;18.44458;1.16000;,
 3.86900;18.44458;1.16000;,
 3.86900;15.31458;1.16000;,
 6.55900;15.31458;1.16000;,
 3.86900;18.44458;1.16000;,
 3.86900;18.44458;-1.16000;,
 3.86900;15.31458;-1.16000;,
 3.86900;15.31458;1.16000;,
 6.55900;18.44458;-1.16000;,
 3.86900;18.44458;-1.16000;,
 3.86900;15.31458;-1.16000;,
 6.55900;15.31458;-1.16000;,
 -1.34500;33.06958;-0.53800;,
 1.34500;33.06958;-0.53800;,
 1.34500;32.12958;-0.53800;,
 -1.34500;32.12958;-0.53800;,
 1.34500;33.06958;-0.53800;,
 1.34500;33.06958;1.78200;,
 1.34500;32.12958;1.78200;,
 1.34500;32.12958;-0.53800;,
 1.34500;33.06958;1.78200;,
 -1.34500;33.06958;1.78200;,
 -1.34500;32.12958;1.78200;,
 1.34500;32.12958;1.78200;,
 -1.34500;33.06958;1.78200;,
 -1.34500;33.06958;-0.53800;,
 -1.34500;32.12958;-0.53800;,
 -1.34500;32.12958;1.78200;,
 1.34500;33.06958;-0.53800;,
 -1.34500;33.06958;-0.53800;,
 -1.34500;32.12958;-0.53800;,
 1.34500;32.12958;-0.53800;,
 0.00000;34.58600;-3.02651;,
 0.00000;35.94600;-2.09651;,
 0.80540;34.58600;-1.63151;,
 0.00000;35.94600;-2.09651;,
 -0.80540;34.58600;-1.63151;,
 0.00000;35.94600;-2.09651;,
 0.00000;34.58600;-3.02651;,
 0.00000;34.58600;-2.09651;,
 0.00000;34.58600;-3.02651;,
 0.80540;34.58600;-1.63151;,
 -0.80540;34.58600;-1.63151;,
 2.20000;33.41858;-2.20000;,
 -2.20000;33.41858;-2.20000;,
 -2.20000;37.81858;-2.20000;,
 2.20000;37.81858;-2.20000;,
 -2.20000;33.41858;-2.20000;,
 -2.20000;33.41858;2.20000;,
 -2.20000;37.81858;2.20000;,
 -2.20000;37.81858;-2.20000;,
 -2.20000;33.41858;2.20000;,
 2.20000;33.41858;2.20000;,
 2.20000;37.81858;2.20000;,
 -2.20000;37.81858;2.20000;,
 2.20000;33.41858;2.20000;,
 2.20000;33.41858;-2.20000;,
 2.20000;37.81858;-2.20000;,
 2.20000;37.81858;2.20000;,
 2.20000;37.81858;-2.20000;,
 -2.20000;37.81858;-2.20000;,
 -2.20000;33.41858;-2.20000;,
 2.20000;33.41858;-2.20000;,
 3.27500;25.58758;-2.90240;,
 -3.27500;25.58758;-2.90240;,
 -3.27500;32.13758;-2.90240;,
 3.27500;32.13758;-2.90240;,
 -3.27500;25.58758;-2.90240;,
 -3.27500;25.58758;2.80354;,
 -3.27500;32.13758;2.80354;,
 -3.27500;32.13758;-2.90240;,
 -3.27500;25.58758;2.80354;,
 3.27500;25.58758;2.80354;,
 3.27500;32.13758;2.80354;,
 -3.27500;32.13758;2.80354;,
 3.27500;25.58758;2.80354;,
 3.27500;25.58758;-2.90240;,
 3.27500;32.13758;-2.90240;,
 3.27500;32.13758;2.80354;,
 3.27500;32.13758;-2.90240;,
 -3.27500;32.13758;-2.90240;,
 -3.27500;25.58758;-2.90240;,
 3.27500;25.58758;-2.90240;,
 3.00000;21.89358;-2.39689;,
 -3.00000;21.89358;-2.39689;,
 -3.00000;25.02358;-2.39689;,
 3.00000;25.02358;-2.39689;,
 -3.00000;21.89358;-2.39689;,
 -3.00000;21.89358;2.39689;,
 -3.00000;25.02358;2.39689;,
 -3.00000;25.02358;-2.39689;,
 -3.00000;21.89358;2.39689;,
 3.00000;21.89358;2.39689;,
 3.00000;25.02358;2.39689;,
 -3.00000;25.02358;2.39689;,
 3.00000;21.89358;2.39689;,
 3.00000;21.89358;-2.39689;,
 3.00000;25.02358;-2.39689;,
 3.00000;25.02358;2.39689;,
 3.00000;25.02358;-2.39689;,
 -3.00000;25.02358;-2.39689;,
 -3.00000;21.89358;-2.39689;,
 3.00000;21.89358;-2.39689;,
 3.00000;18.42758;-2.39689;,
 -3.00000;18.42758;-2.39689;,
 -3.00000;21.55758;-2.39689;,
 3.00000;21.55758;-2.39689;,
 -3.00000;18.42758;-2.39689;,
 -3.00000;18.42758;2.39689;,
 -3.00000;21.55758;2.39689;,
 -3.00000;21.55758;-2.39689;,
 -3.00000;18.42758;2.39689;,
 3.00000;18.42758;2.39689;,
 3.00000;21.55758;2.39689;,
 -3.00000;21.55758;2.39689;,
 3.00000;18.42758;2.39689;,
 3.00000;18.42758;-2.39689;,
 3.00000;21.55758;-2.39689;,
 3.00000;21.55758;2.39689;,
 3.00000;21.55758;-2.39689;,
 -3.00000;21.55758;-2.39689;,
 -3.00000;18.42758;-2.39689;,
 3.00000;18.42758;-2.39689;,
 -0.49400;10.12858;-1.31000;,
 -3.11400;10.12858;-1.31000;,
 -3.11400;17.86858;-1.31000;,
 -0.49400;17.86858;-1.31000;,
 -3.11400;10.12858;-1.31000;,
 -3.11400;10.12858;1.31000;,
 -3.11400;17.86858;1.31000;,
 -3.11400;17.86858;-1.31000;,
 -3.11400;10.12858;1.31000;,
 -0.49400;10.12858;1.31000;,
 -0.49400;17.86858;1.31000;,
 -3.11400;17.86858;1.31000;,
 -0.49400;10.12858;1.31000;,
 -0.49400;10.12858;-1.31000;,
 -0.49400;17.86858;-1.31000;,
 -0.49400;17.86858;1.31000;,
 -0.49400;17.86858;-1.31000;,
 -3.11400;17.86858;-1.31000;,
 -3.11400;10.12858;-1.31000;,
 -0.49400;10.12858;-1.31000;,
 -0.49400;2.63458;-1.31000;,
 -3.11400;2.63458;-1.31000;,
 -3.11400;9.60458;-1.31000;,
 -0.49400;9.60458;-1.31000;,
 -3.11400;2.63458;-1.31000;,
 -3.11400;2.63458;1.31000;,
 -3.11400;9.60458;1.31000;,
 -3.11400;9.60458;-1.31000;,
 -3.11400;2.63458;1.31000;,
 -0.49400;2.63458;1.31000;,
 -0.49400;9.60458;1.31000;,
 -3.11400;9.60458;1.31000;,
 -0.49400;2.63458;1.31000;,
 -0.49400;2.63458;-1.31000;,
 -0.49400;9.60458;-1.31000;,
 -0.49400;9.60458;1.31000;,
 -0.49400;9.60458;-1.31000;,
 -3.11400;9.60458;-1.31000;,
 -3.11400;2.63458;-1.31000;,
 -0.49400;2.63458;-1.31000;,
 -0.49400;0.12058;-2.30300;,
 -3.11400;0.12058;-2.30300;,
 -3.11400;2.55058;-2.30300;,
 -0.49400;2.55058;-2.30300;,
 -3.11400;0.12058;-2.30300;,
 -3.11400;0.12058;1.10700;,
 -3.11400;2.55058;1.10700;,
 -3.11400;2.55058;-2.30300;,
 -3.11400;0.12058;1.10700;,
 -0.49400;0.12058;1.10700;,
 -0.49400;2.55058;1.10700;,
 -3.11400;2.55058;1.10700;,
 -0.49400;0.12058;1.10700;,
 -0.49400;0.12058;-2.30300;,
 -0.49400;2.55058;-2.30300;,
 -0.49400;2.55058;1.10700;,
 -0.49400;2.55058;-2.30300;,
 -3.11400;2.55058;-2.30300;,
 -3.11400;0.12058;-2.30300;,
 -0.49400;0.12058;-2.30300;,
 -0.88400;0.06158;-4.69500;,
 -2.72400;0.06158;-4.69500;,
 -2.72400;1.41158;-4.69500;,
 -0.88400;1.41158;-4.69500;,
 -2.72400;0.06158;-4.69500;,
 -2.72400;0.06158;-2.77500;,
 -2.72400;1.41158;-2.77500;,
 -2.72400;1.41158;-4.69500;,
 -2.72400;0.06158;-2.77500;,
 -0.88400;0.06158;-2.77500;,
 -0.88400;1.41158;-2.77500;,
 -2.72400;1.41158;-2.77500;,
 -0.88400;0.06158;-2.77500;,
 -0.88400;0.06158;-4.69500;,
 -0.88400;1.41158;-4.69500;,
 -0.88400;1.41158;-2.77500;,
 -0.88400;1.41158;-4.69500;,
 -2.72400;1.41158;-4.69500;,
 -2.72400;0.06158;-4.69500;,
 -0.88400;0.06158;-4.69500;,
 -3.45400;27.74058;-2.32500;,
 -6.97400;27.74058;-2.32500;,
 -6.97400;32.65058;-2.32500;,
 -3.45400;32.65058;-2.32500;,
 -6.97400;27.74058;-2.32500;,
 -6.97400;27.74058;2.32500;,
 -6.97400;32.65058;2.32500;,
 -6.97400;32.65058;-2.32500;,
 -6.97400;27.74058;2.32500;,
 -3.45400;27.74058;2.32500;,
 -3.45400;32.65058;2.32500;,
 -6.97400;32.65058;2.32500;,
 -3.45400;27.74058;2.32500;,
 -3.45400;27.74058;-2.32500;,
 -3.45400;32.65058;-2.32500;,
 -3.45400;32.65058;2.32500;,
 -3.45400;32.65058;-2.32500;,
 -6.97400;32.65058;-2.32500;,
 -6.97400;27.74058;-2.32500;,
 -3.45400;27.74058;-2.32500;,
 -4.05900;24.00458;-0.97000;,
 -6.36900;24.00458;-0.97000;,
 -6.36900;27.43458;-0.97000;,
 -4.05900;27.43458;-0.97000;,
 -6.36900;24.00458;-0.97000;,
 -6.36900;24.00458;0.97000;,
 -6.36900;27.43458;0.97000;,
 -6.36900;27.43458;-0.97000;,
 -6.36900;24.00458;0.97000;,
 -4.05900;24.00458;0.97000;,
 -4.05900;27.43458;0.97000;,
 -6.36900;27.43458;0.97000;,
 -4.05900;24.00458;0.97000;,
 -4.05900;24.00458;-0.97000;,
 -4.05900;27.43458;-0.97000;,
 -4.05900;27.43458;0.97000;,
 -4.05900;27.43458;-0.97000;,
 -6.36900;27.43458;-0.97000;,
 -6.36900;24.00458;-0.97000;,
 -4.05900;24.00458;-0.97000;,
 -4.05900;18.70258;-0.97000;,
 -6.36900;18.70258;-0.97000;,
 -6.36900;23.45258;-0.97000;,
 -4.05900;23.45258;-0.97000;,
 -6.36900;18.70258;-0.97000;,
 -6.36900;18.70258;0.97000;,
 -6.36900;23.45258;0.97000;,
 -6.36900;23.45258;-0.97000;,
 -6.36900;18.70258;0.97000;,
 -4.05900;18.70258;0.97000;,
 -4.05900;23.45258;0.97000;,
 -6.36900;23.45258;0.97000;,
 -4.05900;18.70258;0.97000;,
 -4.05900;18.70258;-0.97000;,
 -4.05900;23.45258;-0.97000;,
 -4.05900;23.45258;0.97000;,
 -4.05900;23.45258;-0.97000;,
 -6.36900;23.45258;-0.97000;,
 -6.36900;18.70258;-0.97000;,
 -4.05900;18.70258;-0.97000;,
 -3.86900;15.31458;-1.16000;,
 -6.55900;15.31458;-1.16000;,
 -6.55900;18.44458;-1.16000;,
 -3.86900;18.44458;-1.16000;,
 -6.55900;15.31458;-1.16000;,
 -6.55900;15.31458;1.16000;,
 -6.55900;18.44458;1.16000;,
 -6.55900;18.44458;-1.16000;,
 -6.55900;15.31458;1.16000;,
 -3.86900;15.31458;1.16000;,
 -3.86900;18.44458;1.16000;,
 -6.55900;18.44458;1.16000;,
 -3.86900;15.31458;1.16000;,
 -3.86900;15.31458;-1.16000;,
 -3.86900;18.44458;-1.16000;,
 -3.86900;18.44458;1.16000;,
 -3.86900;18.44458;-1.16000;,
 -6.55900;18.44458;-1.16000;,
 -6.55900;15.31458;-1.16000;,
 -3.86900;15.31458;-1.16000;,
 1.34500;32.12958;-0.53800;,
 -1.34500;32.12958;-0.53800;,
 -1.34500;33.06958;-0.53800;,
 1.34500;33.06958;-0.53800;,
 -1.34500;32.12958;-0.53800;,
 -1.34500;32.12958;1.78200;,
 -1.34500;33.06958;1.78200;,
 -1.34500;33.06958;-0.53800;,
 -1.34500;32.12958;1.78200;,
 1.34500;32.12958;1.78200;,
 1.34500;33.06958;1.78200;,
 -1.34500;33.06958;1.78200;,
 1.34500;32.12958;1.78200;,
 1.34500;32.12958;-0.53800;,
 1.34500;33.06958;-0.53800;,
 1.34500;33.06958;1.78200;,
 1.34500;33.06958;-0.53800;,
 -1.34500;33.06958;-0.53800;,
 -1.34500;32.12958;-0.53800;,
 1.34500;32.12958;-0.53800;,
 -0.80540;34.58600;-1.63151;,
 0.80540;34.58600;-1.63151;,
 -0.80540;34.58600;-1.63151;,
 0.80540;34.58600;-1.63151;;
 
 168;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;192,185,196,197;,
 4;198,199,186,195;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;212,205,216,217;,
 4;218,219,206,215;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;232,225,236,237;,
 4;238,239,226,235;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;252,245,256,257;,
 4;258,259,246,255;,
 3;260,261,262;,
 3;262,263,264;,
 3;264,265,266;,
 3;267,268,269;,
 3;267,269,270;,
 3;267,270,268;,
 4;271,272,273,274;,
 4;275,276,277,278;,
 4;279,280,281,282;,
 4;283,284,285,286;,
 4;287,288,277,286;,
 4;283,276,289,290;,
 4;291,292,293,294;,
 4;295,296,297,298;,
 4;299,300,301,302;,
 4;303,304,305,306;,
 4;307,308,297,306;,
 4;303,296,309,310;,
 4;311,312,313,314;,
 4;315,316,317,318;,
 4;319,320,321,322;,
 4;323,324,325,326;,
 4;327,328,317,326;,
 4;323,316,329,330;,
 4;331,332,333,334;,
 4;335,336,337,338;,
 4;339,340,341,342;,
 4;343,344,345,346;,
 4;347,348,337,346;,
 4;343,336,349,350;,
 4;351,352,353,354;,
 4;355,356,357,358;,
 4;359,360,361,362;,
 4;363,364,365,366;,
 4;367,368,357,366;,
 4;363,356,369,370;,
 4;371,372,373,374;,
 4;375,376,377,378;,
 4;379,380,381,382;,
 4;383,384,385,386;,
 4;387,388,377,386;,
 4;383,376,389,390;,
 4;391,392,393,394;,
 4;395,396,397,398;,
 4;399,400,401,402;,
 4;403,404,405,406;,
 4;407,408,397,406;,
 4;403,396,409,410;,
 4;411,412,413,414;,
 4;415,416,417,418;,
 4;419,420,421,422;,
 4;423,424,425,426;,
 4;427,428,417,426;,
 4;423,416,429,430;,
 4;431,432,433,434;,
 4;435,436,437,438;,
 4;439,440,441,442;,
 4;443,444,445,446;,
 4;447,448,437,446;,
 4;443,436,449,450;,
 4;451,452,453,454;,
 4;455,456,457,458;,
 4;459,460,461,462;,
 4;463,464,465,466;,
 4;467,468,457,466;,
 4;463,456,469,470;,
 4;471,472,473,474;,
 4;475,476,477,478;,
 4;479,480,481,482;,
 4;483,484,485,486;,
 4;487,488,477,486;,
 4;483,476,489,490;,
 4;491,492,493,494;,
 4;495,496,497,498;,
 4;499,500,501,502;,
 4;503,504,505,506;,
 4;507,508,497,506;,
 4;503,496,509,510;,
 4;511,512,513,514;,
 4;515,516,517,518;,
 4;519,520,521,522;,
 4;523,524,525,526;,
 4;527,528,517,526;,
 4;523,516,529,530;,
 3;531,261,260;,
 3;532,263,531;,
 3;266,265,532;,
 3;533,268,267;,
 3;534,533,267;,
 3;268,534,267;;
 
 MeshMaterialList {
  4;
  168;
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.614902;0.436078;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.153725;0.109020;;
  }
  Material {
   0.800000;0.040784;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.010196;0.000000;;
  }
  Material {
   0.006275;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.001569;0.000000;0.200000;;
  }
  Material {
   0.800000;0.771765;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.192941;0.000000;;
  }
 }
 MeshNormals {
  13;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.819451;0.323524;-0.473110;,
  0.819451;0.323524;-0.473110;,
  0.000000;0.323524;0.946220;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.819451;0.323524;-0.473110;,
  0.000000;1.000000;0.000000;,
  -0.819451;0.323524;-0.473110;,
  -0.819451;0.323524;-0.473110;,
  0.819451;0.323524;-0.473110;;
  168;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  3;3,3,4;,
  3;5,5,5;,
  3;10,11,11;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;6,6,6,6;,
  3;8,11,11;,
  3;5,5,5;,
  3;3,3,12;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;;
 }
 MeshTextureCoords {
  535;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.166667;0.000000;,
  0.333333;1.000000;,
  0.333333;0.000000;,
  0.666667;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.333333;1.000000;,
  0.666667;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}