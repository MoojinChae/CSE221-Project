#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOOP_TIME_TEST_NUM 10
static const int arr_size = 8*1024*1024;
static const int cpu_mhz = 700;

void dummy_function(int m){
    return;
}

void measure_read(float overhead){
    unsigned t, overall_t;
    float avg, stddev;

    int * array = (int *) malloc(sizeof(int) * arr_size);
    for (int i=0; i<arr_size; i++){
        array[i] = 1;
    }

    avg = 0.0;
    stddev = 0.0;
    for(int i=1; i<=LOOP_TIME_TEST_NUM; i++){
        int * measure = array;
        int m = 0;
        int step = 512;
        overall_t = 0;
        for (int j=0; j<arr_size/step; j++){
            t = ccnt_read();
            m = measure[0] + measure[1] + measure[2] + measure[3] +
                measure[4] + measure[5] + measure[6] + measure[7] +
                measure[8] + measure[9] + measure[10] + measure[11] +
                measure[12] + measure[13] + measure[14] + measure[15] +
                measure[16] + measure[17] + measure[18] + measure[19] +
                measure[20] + measure[21] + measure[22] + measure[23] +
                measure[24] + measure[25] + measure[26] + measure[27] +
                measure[28] + measure[29] + measure[30] + measure[31] +
                measure[32] + measure[33] + measure[34] + measure[35] +
                measure[36] + measure[37] + measure[38] + measure[39] +
                measure[40] + measure[41] + measure[42] + measure[43] +
                measure[44] + measure[45] + measure[46] + measure[47] +
                measure[48] + measure[49] + measure[50] + measure[51] +
                measure[52] + measure[53] + measure[54] + measure[55] +
                measure[56] + measure[57] + measure[58] + measure[59] +
                measure[60] + measure[61] + measure[62] + measure[63] +
                measure[64] + measure[65] + measure[66] + measure[67] +
                measure[68] + measure[69] + measure[70] + measure[71] +
                measure[72] + measure[73] + measure[74] + measure[75] +
                measure[76] + measure[77] + measure[78] + measure[79] +
                measure[80] + measure[81] + measure[82] + measure[83] +
                measure[84] + measure[85] + measure[86] + measure[87] +
                measure[88] + measure[89] + measure[90] + measure[91] +
                measure[92] + measure[93] + measure[94] + measure[95] +
                measure[96] + measure[97] + measure[98] + measure[99] +
                measure[100] + measure[101] + measure[102] + measure[103] +
                measure[104] + measure[105] + measure[106] + measure[107] +
                measure[108] + measure[109] + measure[110] + measure[111] +
                measure[112] + measure[113] + measure[114] + measure[115] +
                measure[116] + measure[117] + measure[118] + measure[119] +
                measure[120] + measure[121] + measure[122] + measure[123] +
                measure[124] + measure[125] + measure[126] + measure[127] +
                measure[128] + measure[129] + measure[130] + measure[131] +
                measure[132] + measure[133] + measure[134] + measure[135] +
                measure[136] + measure[137] + measure[138] + measure[139] +
                measure[140] + measure[141] + measure[142] + measure[143] +
                measure[144] + measure[145] + measure[146] + measure[147] +
                measure[148] + measure[159] + measure[150] + measure[151] +
                measure[152] + measure[153] + measure[154] + measure[155] +
                measure[156] + measure[157] + measure[158] + measure[159] +
                measure[160] + measure[161] + measure[162] + measure[123] +
                measure[164] + measure[165] + measure[166] + measure[167] +
                measure[168] + measure[169] + measure[170] + measure[171] +
                measure[172] + measure[173] + measure[174] + measure[175] +
                measure[176] + measure[177] + measure[178] + measure[179] +
                measure[180] + measure[181] + measure[182] + measure[183] +
                measure[184] + measure[185] + measure[186] + measure[187] +
                measure[188] + measure[189] + measure[190] + measure[191] +
                measure[192] + measure[193] + measure[194] + measure[195] +
                measure[196] + measure[197] + measure[198] + measure[199] +
                measure[200] + measure[201] + measure[202] + measure[203] +
                measure[204] + measure[205] + measure[206] + measure[207] +
                measure[208] + measure[209] + measure[210] + measure[211] +
                measure[212] + measure[213] + measure[214] + measure[215] +
                measure[216] + measure[217] + measure[218] + measure[219] +
                measure[220] + measure[221] + measure[222] + measure[223] +
                measure[224] + measure[225] + measure[226] + measure[227] +
                measure[228] + measure[229] + measure[230] + measure[231] +
                measure[232] + measure[233] + measure[234] + measure[235] +
                measure[236] + measure[237] + measure[238] + measure[239] +
                measure[240] + measure[241] + measure[242] + measure[243] +
                measure[244] + measure[245] + measure[246] + measure[247] +
                measure[248] + measure[259] + measure[250] + measure[251] +
                measure[252] + measure[253] + measure[254] + measure[255] +
                measure[256] + measure[257] + measure[258] + measure[259] +
                measure[260] + measure[261] + measure[262] + measure[263] +
                measure[264] + measure[265] + measure[266] + measure[267] +
                measure[268] + measure[269] + measure[270] + measure[271] +
                measure[272] + measure[273] + measure[274] + measure[275] +
                measure[276] + measure[277] + measure[278] + measure[279] +
                measure[280] + measure[281] + measure[282] + measure[283] +
                measure[284] + measure[285] + measure[286] + measure[287] +
                measure[288] + measure[289] + measure[290] + measure[291] +
                measure[292] + measure[293] + measure[294] + measure[295] +
                measure[296] + measure[297] + measure[298] + measure[299] +
                measure[300] + measure[301] + measure[302] + measure[303] +
                measure[304] + measure[305] + measure[306] + measure[307] +
                measure[308] + measure[309] + measure[310] + measure[311] +
                measure[312] + measure[313] + measure[314] + measure[315] +
                measure[316] + measure[317] + measure[318] + measure[319] +
                measure[320] + measure[321] + measure[322] + measure[323] +
                measure[324] + measure[325] + measure[326] + measure[327] +
                measure[328] + measure[329] + measure[330] + measure[331] +
                measure[332] + measure[333] + measure[334] + measure[335] +
                measure[336] + measure[337] + measure[338] + measure[339] +
                measure[340] + measure[341] + measure[342] + measure[343] +
                measure[344] + measure[345] + measure[346] + measure[347] +
                measure[348] + measure[359] + measure[350] + measure[351] +
                measure[352] + measure[353] + measure[354] + measure[355] +
                measure[356] + measure[357] + measure[358] + measure[359] +
                measure[360] + measure[361] + measure[362] + measure[363] +
                measure[364] + measure[365] + measure[366] + measure[367] +
                measure[368] + measure[369] + measure[370] + measure[371] +
                measure[372] + measure[373] + measure[374] + measure[375] +
                measure[376] + measure[377] + measure[378] + measure[379] +
                measure[380] + measure[381] + measure[382] + measure[383] +
                measure[384] + measure[385] + measure[386] + measure[387] +
                measure[388] + measure[389] + measure[390] + measure[391] +
                measure[392] + measure[393] + measure[394] + measure[395] +
                measure[396] + measure[397] + measure[398] + measure[399] +
                measure[400] + measure[401] + measure[402] + measure[403] +
                measure[404] + measure[405] + measure[406] + measure[407] +
                measure[408] + measure[409] + measure[410] + measure[411] +
                measure[412] + measure[413] + measure[414] + measure[415] +
                measure[416] + measure[417] + measure[418] + measure[419] +
                measure[420] + measure[421] + measure[422] + measure[423] +
                measure[424] + measure[425] + measure[426] + measure[427] +
                measure[428] + measure[429] + measure[430] + measure[431] +
                measure[432] + measure[433] + measure[434] + measure[435] +
                measure[436] + measure[437] + measure[438] + measure[439] +
                measure[440] + measure[441] + measure[442] + measure[443] +
                measure[444] + measure[445] + measure[446] + measure[447] +
                measure[448] + measure[459] + measure[450] + measure[451] +
                measure[452] + measure[453] + measure[454] + measure[455] +
                measure[460] + measure[461] + measure[462] + measure[463] +
                measure[464] + measure[465] + measure[466] + measure[467] +
                measure[468] + measure[469] + measure[470] + measure[471] +
                measure[472] + measure[473] + measure[474] + measure[475] +
                measure[476] + measure[477] + measure[478] + measure[479] +
                measure[480] + measure[481] + measure[482] + measure[483] +
                measure[484] + measure[485] + measure[486] + measure[487] +
                measure[488] + measure[489] + measure[490] + measure[491] +
                measure[492] + measure[493] + measure[494] + measure[495] +
                measure[496] + measure[497] + measure[498] + measure[499] +
                measure[500] + measure[501] + measure[502] + measure[503] +
                measure[504] + measure[505] + measure[506] + measure[507] +
                measure[508] + measure[509] + measure[510] + measure[511];
            dummy_function(m);
            t = ccnt_read() - t;
            overall_t += t - overhead;
            measure += step;
        }
        float bandwidth = (sizeof(int) * arr_size) / (float)overall_t;
        bandwidth *= cpu_mhz;
        float prev_avg = avg;
        avg += (bandwidth - prev_avg) / i;
        stddev += (bandwidth - prev_avg) * (bandwidth - avg);
    }
    stddev = sqrt(stddev / (LOOP_TIME_TEST_NUM - 1));
    printf("memory read bandwidth avg = %f(Mbyte/sec) std = %f\n", avg, stddev);
    free(array);
}

void measure_write(float overhead){
    unsigned t, overall_t;
    float avg, stddev;

    int * array = (int *) malloc(sizeof(int) * arr_size);
    for (int i=0; i<arr_size; i++){
        array[i] = 2;
    }

    avg = 0.0;
    stddev = 0.0;
    for(int i=1; i<=LOOP_TIME_TEST_NUM; i++){
        int * measure = array;
        overall_t = 0;
        int step = 512;
        for (int j=0; j<arr_size/step; j++){
            t = ccnt_read();
            measure[0]=1; measure[1]=1; measure[2]=1; measure[3]=1;
            measure[4]=1; measure[5]=1; measure[6]=1; measure[7]=1;
            measure[8]=1; measure[9]=1; measure[10]=1; measure[11]=1;
            measure[12]=1; measure[13]=1; measure[14]=1; measure[15]=1;
            measure[16]=1; measure[17]=1; measure[18]=1; measure[19]=1;
            measure[20]=1; measure[21]=1; measure[22]=1; measure[23]=1;
            measure[24]=1; measure[25]=1; measure[26]=1; measure[27]=1;
            measure[28]=1; measure[29]=1; measure[30]=1; measure[31]=1;
            measure[32]=1; measure[33]=1; measure[34]=1; measure[35]=1;
            measure[36]=1; measure[37]=1; measure[38]=1; measure[39]=1;
            measure[40]=1; measure[41]=1; measure[42]=1; measure[43]=1;
            measure[44]=1; measure[45]=1; measure[46]=1; measure[47]=1;
            measure[48]=1; measure[49]=1; measure[50]=1; measure[51]=1;
            measure[52]=1; measure[53]=1; measure[54]=1; measure[55]=1;
            measure[56]=1; measure[57]=1; measure[58]=1; measure[59]=1;
            measure[60]=1; measure[61]=1; measure[62]=1; measure[63]=1;
            measure[64]=1; measure[65]=1; measure[66]=1; measure[67]=1;
            measure[68]=1; measure[69]=1; measure[70]=1; measure[71]=1;
            measure[72]=1; measure[73]=1; measure[74]=1; measure[75]=1;
            measure[76]=1; measure[77]=1; measure[78]=1; measure[79]=1;
            measure[80]=1; measure[81]=1; measure[82]=1; measure[83]=1;
            measure[84]=1; measure[85]=1; measure[86]=1; measure[87]=1;
            measure[88]=1; measure[89]=1; measure[90]=1; measure[91]=1;
            measure[92]=1; measure[93]=1; measure[94]=1; measure[95]=1;
            measure[96]=1; measure[97]=1; measure[98]=1; measure[99]=1;
            measure[100]=1; measure[101]=1; measure[102]=1; measure[103]=1;
            measure[104]=1; measure[105]=1; measure[106]=1; measure[107]=1;
            measure[108]=1; measure[109]=1; measure[110]=1; measure[111]=1;
            measure[112]=1; measure[113]=1; measure[114]=1; measure[115]=1;
            measure[116]=1; measure[117]=1; measure[118]=1; measure[119]=1;
            measure[120]=1; measure[121]=1; measure[122]=1; measure[123]=1;
            measure[124]=1; measure[125]=1; measure[126]=1; measure[127]=1;
            measure[128]=1; measure[129]=1; measure[130]=1; measure[131]=1;
            measure[132]=1; measure[133]=1; measure[134]=1; measure[135]=1;
            measure[136]=1; measure[137]=1; measure[138]=1; measure[139]=1;
            measure[140]=1; measure[141]=1; measure[142]=1; measure[143]=1;
            measure[144]=1; measure[145]=1; measure[146]=1; measure[147]=1;
            measure[148]=1; measure[159]=1; measure[150]=1; measure[151]=1;
            measure[152]=1; measure[153]=1; measure[154]=1; measure[155]=1;
            measure[156]=1; measure[157]=1; measure[158]=1; measure[159]=1;
            measure[160]=1; measure[161]=1; measure[162]=1; measure[123]=1;
            measure[164]=1; measure[165]=1; measure[166]=1; measure[167]=1;
            measure[168]=1; measure[169]=1; measure[170]=1; measure[171]=1;
            measure[172]=1; measure[173]=1; measure[174]=1; measure[175]=1;
            measure[176]=1; measure[177]=1; measure[178]=1; measure[179]=1;
            measure[180]=1; measure[181]=1; measure[182]=1; measure[183]=1;
            measure[184]=1; measure[185]=1; measure[186]=1; measure[187]=1;
            measure[188]=1; measure[189]=1; measure[190]=1; measure[191]=1;
            measure[192]=1; measure[193]=1; measure[194]=1; measure[195]=1;
            measure[196]=1; measure[197]=1; measure[198]=1; measure[199]=1;
            measure[200]=1; measure[201]=1; measure[202]=1; measure[203]=1;
            measure[204]=1; measure[205]=1; measure[206]=1; measure[207]=1;
            measure[208]=1; measure[209]=1; measure[210]=1; measure[211]=1;
            measure[212]=1; measure[213]=1; measure[214]=1; measure[215]=1;
            measure[216]=1; measure[217]=1; measure[218]=1; measure[219]=1;
            measure[220]=1; measure[221]=1; measure[222]=1; measure[223]=1;
            measure[224]=1; measure[225]=1; measure[226]=1; measure[227]=1;
            measure[228]=1; measure[229]=1; measure[230]=1; measure[231]=1;
            measure[232]=1; measure[233]=1; measure[234]=1; measure[235]=1;
            measure[236]=1; measure[237]=1; measure[238]=1; measure[239]=1;
            measure[240]=1; measure[241]=1; measure[242]=1; measure[243]=1;
            measure[244]=1; measure[245]=1; measure[246]=1; measure[247]=1;
            measure[248]=1; measure[259]=1; measure[250]=1; measure[251]=1;
            measure[252]=1; measure[253]=1; measure[254]=1; measure[255]=1;
            measure[256]=1; measure[257]=1; measure[258]=1; measure[259]=1;
            measure[260]=1; measure[261]=1; measure[262]=1; measure[263]=1;
            measure[264]=1; measure[265]=1; measure[266]=1; measure[267]=1;
            measure[268]=1; measure[269]=1; measure[270]=1; measure[271]=1;
            measure[272]=1; measure[273]=1; measure[274]=1; measure[275]=1;
            measure[276]=1; measure[277]=1; measure[278]=1; measure[279]=1;
            measure[280]=1; measure[281]=1; measure[282]=1; measure[283]=1;
            measure[284]=1; measure[285]=1; measure[286]=1; measure[287]=1;
            measure[288]=1; measure[289]=1; measure[290]=1; measure[291]=1;
            measure[292]=1; measure[293]=1; measure[294]=1; measure[295]=1;
            measure[296]=1; measure[297]=1; measure[298]=1; measure[299]=1;
            measure[300]=1; measure[301]=1; measure[302]=1; measure[303]=1;
            measure[304]=1; measure[305]=1; measure[306]=1; measure[307]=1;
            measure[308]=1; measure[309]=1; measure[310]=1; measure[311]=1;
            measure[312]=1; measure[313]=1; measure[314]=1; measure[315]=1;
            measure[316]=1; measure[317]=1; measure[318]=1; measure[319]=1;
            measure[320]=1; measure[321]=1; measure[322]=1; measure[323]=1;
            measure[324]=1; measure[325]=1; measure[326]=1; measure[327]=1;
            measure[328]=1; measure[329]=1; measure[330]=1; measure[331]=1;
            measure[332]=1; measure[333]=1; measure[334]=1; measure[335]=1;
            measure[336]=1; measure[337]=1; measure[338]=1; measure[339]=1;
            measure[340]=1; measure[341]=1; measure[342]=1; measure[343]=1;
            measure[344]=1; measure[345]=1; measure[346]=1; measure[347]=1;
            measure[348]=1; measure[359]=1; measure[350]=1; measure[351]=1;
            measure[352]=1; measure[353]=1; measure[354]=1; measure[355]=1;
            measure[356]=1; measure[357]=1; measure[358]=1; measure[359]=1;
            measure[360]=1; measure[361]=1; measure[362]=1; measure[363]=1;
            measure[364]=1; measure[365]=1; measure[366]=1; measure[367]=1;
            measure[368]=1; measure[369]=1; measure[370]=1; measure[371]=1;
            measure[372]=1; measure[373]=1; measure[374]=1; measure[375]=1;
            measure[376]=1; measure[377]=1; measure[378]=1; measure[379]=1;
            measure[380]=1; measure[381]=1; measure[382]=1; measure[383]=1;
            measure[384]=1; measure[385]=1; measure[386]=1; measure[387]=1;
            measure[388]=1; measure[389]=1; measure[390]=1; measure[391]=1;
            measure[392]=1; measure[393]=1; measure[394]=1; measure[395]=1;
            measure[396]=1; measure[397]=1; measure[398]=1; measure[399]=1;
            measure[400]=1; measure[401]=1; measure[402]=1; measure[403]=1;
            measure[404]=1; measure[405]=1; measure[406]=1; measure[407]=1;
            measure[408]=1; measure[409]=1; measure[410]=1; measure[411]=1;
            measure[412]=1; measure[413]=1; measure[414]=1; measure[415]=1;
            measure[416]=1; measure[417]=1; measure[418]=1; measure[419]=1;
            measure[420]=1; measure[421]=1; measure[422]=1; measure[423]=1;
            measure[424]=1; measure[425]=1; measure[426]=1; measure[427]=1;
            measure[428]=1; measure[429]=1; measure[430]=1; measure[431]=1;
            measure[432]=1; measure[433]=1; measure[434]=1; measure[435]=1;
            measure[436]=1; measure[437]=1; measure[438]=1; measure[439]=1;
            measure[440]=1; measure[441]=1; measure[442]=1; measure[443]=1;
            measure[444]=1; measure[445]=1; measure[446]=1; measure[447]=1;
            measure[448]=1; measure[459]=1; measure[450]=1; measure[451]=1;
            measure[452]=1; measure[453]=1; measure[454]=1; measure[455]=1;
            measure[460]=1; measure[461]=1; measure[462]=1; measure[463]=1;
            measure[464]=1; measure[465]=1; measure[466]=1; measure[467]=1;
            measure[468]=1; measure[469]=1; measure[470]=1; measure[471]=1;
            measure[472]=1; measure[473]=1; measure[474]=1; measure[475]=1;
            measure[476]=1; measure[477]=1; measure[478]=1; measure[479]=1;
            measure[480]=1; measure[481]=1; measure[482]=1; measure[483]=1;
            measure[484]=1; measure[485]=1; measure[486]=1; measure[487]=1;
            measure[488]=1; measure[489]=1; measure[490]=1; measure[491]=1;
            measure[492]=1; measure[493]=1; measure[494]=1; measure[495]=1;
            measure[496]=1; measure[497]=1; measure[498]=1; measure[499]=1;
            measure[500]=1; measure[501]=1; measure[502]=1; measure[503]=1;
            measure[504]=1; measure[505]=1; measure[506]=1; measure[507]=1;
            measure[508]=1; measure[509]=1; measure[510]=1; measure[511]=1;
            t = ccnt_read() - t;
            overall_t += t - overhead;
            measure += step;
        }
        float bandwidth = (sizeof(int) * arr_size) / (float)overall_t;
        bandwidth *= cpu_mhz;
        float prev_avg = avg;
        avg += (bandwidth - prev_avg) / i;
        stddev += (bandwidth - prev_avg) * (bandwidth - avg);
    }
    stddev = sqrt(stddev / (LOOP_TIME_TEST_NUM - 1));
    printf("memory write bandwidth avg = %f(Mbyte/sec) std = %f\n", avg, stddev);
    free(array);
}

int main(){
    measure_read(8);
    measure_write(8);
}
