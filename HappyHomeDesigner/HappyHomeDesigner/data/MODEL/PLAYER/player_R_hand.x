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
 32;
 -3.45400;32.65058;-2.32500;,
 -3.45400;27.74058;-2.32500;,
 -6.97400;27.74058;-2.32500;,
 -6.97400;32.65058;-2.32500;,
 -6.97400;27.74058;2.32500;,
 -6.97400;32.65058;2.32500;,
 -3.45400;27.74058;2.32500;,
 -3.45400;32.65058;2.32500;,
 -4.05900;27.43458;-0.97000;,
 -4.05900;24.00458;-0.97000;,
 -6.36900;24.00458;-0.97000;,
 -6.36900;27.43458;-0.97000;,
 -6.36900;24.00458;0.97000;,
 -6.36900;27.43458;0.97000;,
 -4.05900;24.00458;0.97000;,
 -4.05900;27.43458;0.97000;,
 -4.05900;23.45258;-0.97000;,
 -4.05900;18.70258;-0.97000;,
 -6.36900;18.70258;-0.97000;,
 -6.36900;23.45258;-0.97000;,
 -6.36900;18.70258;0.97000;,
 -6.36900;23.45258;0.97000;,
 -4.05900;18.70258;0.97000;,
 -4.05900;23.45258;0.97000;,
 -3.86900;18.44458;-1.16000;,
 -3.86900;15.31458;-1.16000;,
 -6.55900;15.31458;-1.16000;,
 -6.55900;18.44458;-1.16000;,
 -6.55900;15.31458;1.16000;,
 -6.55900;18.44458;1.16000;,
 -3.86900;15.31458;1.16000;,
 -3.86900;18.44458;1.16000;;
 
 24;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,1,0;,
 4;7,0,3,5;,
 4;1,6,4,2;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,9,8;,
 4;15,8,11,13;,
 4;9,14,12,10;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,17,16;,
 4;23,16,19,21;,
 4;17,22,20,18;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,25,24;,
 4;31,24,27,29;,
 4;25,30,28,26;;
 
 MeshMaterialList {
  4;
  24;
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
  0;;
  Material {
   0.800000;0.615200;0.436000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.153800;0.109000;;
  }
  Material {
   0.800000;0.040800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.010200;0.000000;;
  }
  Material {
   0.006400;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.001600;0.000000;0.200000;;
  }
  Material {
   0.800000;0.772000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.193000;0.000000;;
  }
 }
 MeshNormals {
  6;
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  24;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;;
 }
}
