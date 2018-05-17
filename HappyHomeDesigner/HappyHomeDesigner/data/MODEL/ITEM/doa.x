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
 99;
 -13.84790;20.18588;-0.47483;,
 0.04865;20.18588;-0.47483;,
 0.04865;0.18587;-0.47483;,
 -13.84790;0.18587;-0.47483;,
 0.04865;20.18588;-0.47483;,
 0.04865;20.18588;0.47483;,
 0.04865;0.18587;0.47483;,
 0.04865;0.18587;-0.47483;,
 0.04865;20.18588;0.47483;,
 -13.84790;20.18588;0.47483;,
 -13.84790;0.18587;0.47483;,
 0.04865;0.18587;0.47483;,
 -13.84790;20.18588;0.47483;,
 -13.84790;20.18588;-0.47483;,
 -13.84790;0.18587;-0.47483;,
 -13.84790;0.18587;0.47483;,
 0.04865;20.18588;-0.47483;,
 -13.84790;20.18588;-0.47483;,
 -13.84790;0.18587;-0.47483;,
 0.04865;0.18587;-0.47483;,
 -11.52416;12.17512;-0.37175;,
 -11.14682;12.06898;-0.43347;,
 -11.52416;12.06898;-0.45904;,
 -11.52416;12.17512;-0.37175;,
 -10.99052;12.06898;-0.37175;,
 -11.52416;12.17512;-0.37175;,
 -11.14682;12.06898;-0.31002;,
 -11.52416;12.17512;-0.37175;,
 -11.52416;12.06898;-0.28446;,
 -11.52416;12.17512;-0.37175;,
 -11.90149;12.06898;-0.31002;,
 -11.52416;12.17512;-0.37175;,
 -12.05779;12.06898;-0.37175;,
 -11.52416;12.17512;-0.37175;,
 -11.90149;12.06898;-0.43347;,
 -11.52416;12.17512;-0.37175;,
 -11.52416;12.06898;-0.45904;,
 -10.82693;11.76670;-0.48580;,
 -11.52416;11.76670;-0.53304;,
 -10.53814;11.76670;-0.37175;,
 -10.82693;11.76670;-0.25770;,
 -11.52416;11.76670;-0.21045;,
 -12.22138;11.76670;-0.25770;,
 -12.51018;11.76670;-0.37175;,
 -12.22138;11.76670;-0.48580;,
 -11.52416;11.76670;-0.53304;,
 -10.61319;11.31430;-0.52076;,
 -11.52416;11.31430;-0.58248;,
 -10.23585;11.31430;-0.37175;,
 -10.61319;11.31430;-0.22273;,
 -11.52416;11.31430;-0.16101;,
 -12.43512;11.31430;-0.22273;,
 -12.81246;11.31430;-0.37175;,
 -12.43512;11.31430;-0.52076;,
 -11.52416;11.31430;-0.58248;,
 -10.53814;10.78067;-0.53304;,
 -11.52416;10.78067;-0.59985;,
 -10.12971;10.78067;-0.37175;,
 -10.53814;10.78067;-0.21045;,
 -11.52416;10.78067;-0.14365;,
 -12.51018;10.78067;-0.21046;,
 -12.91861;10.78067;-0.37175;,
 -12.51018;10.78067;-0.53304;,
 -11.52416;10.78067;-0.59985;,
 -10.61319;10.24703;-0.52076;,
 -11.52416;10.24703;-0.58248;,
 -10.23585;10.24703;-0.37175;,
 -10.61319;10.24703;-0.22273;,
 -11.52416;10.24703;-0.16101;,
 -12.43512;10.24703;-0.22273;,
 -12.81246;10.24703;-0.37175;,
 -12.43512;10.24703;-0.52076;,
 -11.52416;10.24703;-0.58248;,
 -10.82693;9.79464;-0.48580;,
 -11.52416;9.79464;-0.53304;,
 -10.53814;9.79464;-0.37175;,
 -10.82693;9.79464;-0.25770;,
 -11.52416;9.79464;-0.21045;,
 -12.22138;9.79464;-0.25770;,
 -12.51018;9.79464;-0.37175;,
 -12.22138;9.79464;-0.48580;,
 -11.52416;9.79464;-0.53304;,
 -11.14682;9.49236;-0.43347;,
 -11.52416;9.49236;-0.45904;,
 -10.99052;9.49236;-0.37175;,
 -11.14682;9.49236;-0.31002;,
 -11.52416;9.49236;-0.28446;,
 -11.90149;9.49236;-0.31002;,
 -12.05779;9.49236;-0.37175;,
 -11.90149;9.49236;-0.43347;,
 -11.52416;9.49236;-0.45904;,
 -11.52416;9.38621;-0.37175;,
 -11.52416;9.38621;-0.37175;,
 -11.52416;9.38621;-0.37175;,
 -11.52416;9.38621;-0.37175;,
 -11.52416;9.38621;-0.37175;,
 -11.52416;9.38621;-0.37175;,
 -11.52416;9.38621;-0.37175;,
 -11.52416;9.38621;-0.37175;;
 
 70;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 3;20,21,22;,
 3;23,24,21;,
 3;25,26,24;,
 3;27,28,26;,
 3;29,30,28;,
 3;31,32,30;,
 3;33,34,32;,
 3;35,36,34;,
 4;22,21,37,38;,
 4;21,24,39,37;,
 4;24,26,40,39;,
 4;26,28,41,40;,
 4;28,30,42,41;,
 4;30,32,43,42;,
 4;32,34,44,43;,
 4;34,36,45,44;,
 4;38,37,46,47;,
 4;37,39,48,46;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;44,45,54,53;,
 4;47,46,55,56;,
 4;46,48,57,55;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;53,54,63,62;,
 4;56,55,64,65;,
 4;55,57,66,64;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;62,63,72,71;,
 4;65,64,73,74;,
 4;64,66,75,73;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;,
 4;71,72,81,80;,
 4;74,73,82,83;,
 4;73,75,84,82;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;77,78,87,86;,
 4;78,79,88,87;,
 4;79,80,89,88;,
 4;80,81,90,89;,
 3;83,82,91;,
 3;82,84,92;,
 3;84,85,93;,
 3;85,86,94;,
 3;86,87,95;,
 3;87,88,96;,
 3;88,89,97;,
 3;89,90,98;;
 
 MeshMaterialList {
  2;
  70;
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
  1,
  1,
  1,
  1;;
  Material {
   0.633600;0.370400;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.615200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  80;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000001;0.780040;-0.625730;,
  -0.000001;0.447765;-0.894151;,
  0.162252;0.589305;-0.791450;,
  0.271175;0.904524;-0.329091;,
  0.162253;0.589321;0.791438;,
  -0.000001;0.447767;0.894150;,
  -0.162253;0.589320;0.791439;,
  -0.271187;0.904537;0.329044;,
  -0.162252;0.589304;-0.791451;,
  -0.000001;0.173593;-0.984817;,
  0.207236;0.272174;-0.939667;,
  0.342228;0.363145;-0.866606;,
  0.207244;0.272184;0.939662;,
  -0.000001;0.173601;0.984816;,
  -0.207242;0.272183;0.939663;,
  -0.342238;0.363153;0.866598;,
  -0.207234;0.272172;-0.939668;,
  -0.000000;0.070636;-0.997502;,
  0.217657;0.114705;-0.969262;,
  0.362795;0.156156;-0.918692;,
  0.217665;0.114710;0.969259;,
  -0.000002;0.070635;0.997502;,
  -0.217663;0.114704;0.969260;,
  -0.362803;0.156159;0.918689;,
  -0.217655;0.114704;-0.969262;,
  -0.000000;0.000000;-1.000000;,
  0.219898;0.000001;-0.975523;,
  0.367297;0.000001;-0.930104;,
  0.219907;0.000001;0.975521;,
  -0.000003;0.000000;1.000000;,
  -0.219904;0.000000;0.975522;,
  -0.367308;0.000000;0.930099;,
  -0.219898;0.000001;-0.975523;,
  -0.000000;-0.070637;-0.997502;,
  0.217657;-0.114706;-0.969262;,
  0.362795;-0.156158;-0.918692;,
  0.217665;-0.114711;0.969259;,
  -0.000002;-0.070636;0.997502;,
  -0.217663;-0.114707;0.969260;,
  -0.362803;-0.156161;0.918688;,
  -0.217655;-0.114706;-0.969262;,
  -0.000001;-0.173592;-0.984818;,
  0.207236;-0.272175;-0.939667;,
  0.342228;-0.363147;-0.866605;,
  0.207244;-0.272182;0.939663;,
  -0.000001;-0.173595;0.984817;,
  -0.207242;-0.272182;0.939664;,
  -0.342238;-0.363156;0.866597;,
  -0.207234;-0.272172;-0.939668;,
  -0.000001;-0.447743;-0.894163;,
  0.162255;-0.589288;-0.791463;,
  0.258903;-0.709313;-0.655625;,
  0.162257;-0.589301;0.791452;,
  -0.000001;-0.447739;0.894164;,
  -0.162257;-0.589300;0.791453;,
  -0.258917;-0.709335;0.655595;,
  -0.162255;-0.589285;-0.791465;,
  -0.000001;-0.780014;-0.625762;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000001;0.780060;0.625705;,
  0.321895;0.481727;0.815060;,
  0.342243;0.363155;0.866596;,
  -0.321869;0.481719;-0.815075;,
  -0.342223;0.363140;-0.866610;,
  0.362810;0.156164;0.918685;,
  -0.362793;0.156155;-0.918693;,
  0.367317;0.000001;0.930096;,
  -0.367297;0.000001;-0.930104;,
  0.362810;-0.156166;0.918684;,
  -0.362792;-0.156157;-0.918693;,
  0.342243;-0.363159;0.866594;,
  -0.342223;-0.363141;-0.866610;,
  0.258918;-0.709338;0.655592;,
  -0.258902;-0.709309;-0.655630;,
  -0.000001;-0.780034;0.625737;;
  70;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  3;3,5,4;,
  3;3,6,5;,
  3;64,7,6;,
  3;64,8,7;,
  3;64,9,8;,
  3;64,10,9;,
  3;3,11,10;,
  3;3,4,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;65,7,15,66;,
  4;7,8,16,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;67,11,19,68;,
  4;11,4,12,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;66,15,23,69;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;68,19,27,70;,
  4;19,12,20,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;69,23,31,71;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;70,27,35,72;,
  4;27,20,28,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;71,31,39,73;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;72,35,43,74;,
  4;35,28,36,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;73,39,47,75;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;74,43,51,76;,
  4;43,36,44,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;75,47,55,77;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;76,51,59,78;,
  4;51,44,52,59;,
  3;52,53,60;,
  3;53,54,60;,
  3;77,55,79;,
  3;55,56,79;,
  3;56,57,79;,
  3;57,58,79;,
  3;78,59,60;,
  3;59,52,60;;
 }
 MeshTextureCoords {
  99;
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
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}