function [] = savearray(name, array)

fileID = fopen(name,'w');
formatSpec = '%f\n';
fprintf(fileID ,formatSpec, array);
fclose(fileID);
