test_matrix=[12  12  12  12  13  14 ; 13  11  12  25  19  14 ; 14  16  15  11  24  14 ; 15  17  16  13  26  15 ; 15  18  19  16  20  15 ; 16  16  16  16  16  16]

save test_matrix.mat test_matrix;


filter=[1/9 1/9 1/9;1/9 1/9 1/9;1/9 1/9 1/9]

c=conv2(test_matrix, filter,'valid')

d = medfilt2(test_matrix)