// riscv64-linux-gnu-gcc main.c -s -o chall

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void flag_check4(uint64_t* flag_parts) {
    flag_parts[3] -= 10411928656248354;
    flag_parts[0] += 3717008410374606;
    flag_parts[3] += 16161990982726604;
    flag_parts[3] ^= 12716499069622832;
    flag_parts[2] ^= 28539577302538458;
    flag_parts[2] -= 21482968177720845;
    flag_parts[0] += 10048381130959275;
    flag_parts[0] -= 28781946891315813;
    flag_parts[0] -= 8926120424962702;
    flag_parts[2] -= 27789705527605781;
    flag_parts[2] ^= 10956945629724336;
    flag_parts[2] ^= 7590334563060831;
    flag_parts[2] -= 6196670337925742;
    flag_parts[1] ^= 21193537858658163;
    flag_parts[0] -= 25969640247275119;
    flag_parts[2] ^= 31502179943826609;
    flag_parts[1] -= 20080502729067952;
    flag_parts[2] -= 10374343848934765;
    flag_parts[0] -= 20414949046936087;
    flag_parts[0] ^= 23395421414860713;
    flag_parts[2] ^= 14955510668823540;
    flag_parts[1] -= 33762572401269600;
    flag_parts[2] += 15860282678355859;
    flag_parts[2] -= 11319271033281926;
    flag_parts[1] += 15747105345240353;
    flag_parts[2] += 34143574619974739;
    flag_parts[0] += 4363868091317916;
    flag_parts[2] += 31657067439185733;
    flag_parts[1] -= 491225692842278;
    flag_parts[3] += 24247765982296783;
    flag_parts[3] -= 27295362520677283;
    flag_parts[0] ^= 21296569430073383;
    flag_parts[0] -= 2622971706426436;
    flag_parts[3] ^= 24151505162152700;
    flag_parts[3] += 13947173090861564;
    flag_parts[3] -= 11864732570937999;
    flag_parts[0] -= 17075367319767575;
    flag_parts[1] += 2968747397909150;
    flag_parts[2] ^= 34727469992382246;
    flag_parts[0] ^= 16910076275666767;
    flag_parts[1] += 8835488380846686;
    flag_parts[3] += 30370209727110557;
    flag_parts[1] ^= 1824646811293429;
    flag_parts[1] += 31788710633064770;
    flag_parts[3] ^= 18329648784851915;
    flag_parts[3] ^= 10428402152742996;
    flag_parts[0] += 34042558545862203;
}

void flag_check3(uint64_t* flag_parts) {
    flag_parts[2] ^= 9382285201985213;
    flag_parts[2] ^= 9429298559779148;
    flag_parts[2] -= 30793812688345708;
    flag_parts[2] ^= 35669735759247770;
    flag_parts[3] += 29221717201745171;
    flag_parts[3] += 10875215228886800;
    flag_parts[2] -= 11865203606295594;
    flag_parts[2] += 190901888855798;
    flag_parts[2] -= 16539854583133528;
    flag_parts[0] += 25080709854239883;
    flag_parts[2] ^= 14594137883301170;
    flag_parts[2] ^= 13663611637588286;
    flag_parts[3] -= 21236281051675935;
    flag_parts[2] ^= 24037722729843953;
    flag_parts[3] -= 25411738155904496;
    flag_parts[1] ^= 6254873118791181;
    flag_parts[2] ^= 18124486267054701;
    flag_parts[0] += 7044950794088134;
    flag_parts[1] ^= 12034025254272979;
    flag_parts[0] += 20551989546318341;
    flag_parts[1] -= 34639085361917309;
    flag_parts[2] ^= 24591688927030936;
    flag_parts[2] ^= 24355046447923267;
    flag_parts[0] -= 24955442251831423;
    flag_parts[0] += 30470573446260916;
    flag_parts[0] -= 22949659369340648;
    flag_parts[1] += 33536255833867726;
    flag_parts[2] -= 4520271444723856;
    flag_parts[3] += 4791913910145403;
    flag_parts[2] ^= 11986336846883782;
    flag_parts[1] += 6729216721401830;
    flag_parts[2] += 31062775087080115;
    flag_parts[1] -= 7821733177757155;
    flag_parts[1] ^= 19888918613164830;
    flag_parts[0] += 26729375622600444;
    flag_parts[3] ^= 23659088677402632;
    flag_parts[3] -= 11462901485777924;
    flag_parts[2] -= 21105615711051158;
    flag_parts[0] ^= 19557185675982335;
    flag_parts[1] ^= 13228738158200046;
    flag_parts[1] ^= 11307706514319569;
    flag_parts[0] ^= 24931055161923291;
    flag_parts[1] += 32377308429200456;
    flag_parts[3] += 21180359178872217;
    flag_parts[3] -= 5254477018778731;
    flag_parts[0] += 7233309245357536;
    flag_parts[2] ^= 14825373803206588;
    flag_parts[0] ^= 21251602154524279;
    flag_parts[2] ^= 21021828367061373;
    flag_parts[3] ^= 19626003721476025;
    flag_parts[0] -= 10449285357473196;
    flag_parts[1] -= 35926432904568406;
    flag_parts[0] -= 33009485428291434;
    flag_parts[0] += 1166866056060464;
    flag_parts[0] += 9956563986598183;
    flag_parts[2] -= 21811255819147754;
    flag_parts[2] -= 25310165316807840;
    flag_parts[0] ^= 2492857718685689;
    flag_parts[2] ^= 2660168465546561;
    flag_parts[3] ^= 2371195453591823;
    flag_parts[2] ^= 7126970448917242;
    flag_parts[1] += 26391434139888465;
    flag_parts[2] -= 20735850635277473;
}

void flag_check2(uint64_t* flag_parts) {
    flag_parts[0] ^= 336324384392201;
    flag_parts[1] += 10131097025579635;
    flag_parts[1] -= 2529937978634375;
    flag_parts[2] -= 20141992389048032;
    flag_parts[0] ^= 24977761477521219;
    flag_parts[2] -= 10035840016172100;
    flag_parts[1] -= 21447034003522535;
    flag_parts[0] ^= 15960380944924180;
    flag_parts[3] ^= 30932220731384312;
    flag_parts[2] += 20523046709214970;
    flag_parts[2] += 11262860765786900;
    flag_parts[2] ^= 35979427919596539;
    flag_parts[1] += 9871389176715885;
    flag_parts[3] += 11797319870847917;
    flag_parts[2] -= 25773369025092961;
    flag_parts[0] ^= 6202893169040888;
    flag_parts[2] ^= 25040234758950775;
    flag_parts[2] -= 13931099222450539;
    flag_parts[0] += 5690678658912375;
    flag_parts[2] += 22174265874429337;
    flag_parts[3] += 33639712982049518;
    flag_parts[0] ^= 2860499670471807;
    flag_parts[0] -= 29500076320994071;
    flag_parts[0] ^= 17628153874248449;
    flag_parts[0] ^= 34836922780282544;
    flag_parts[0] += 13496872953068949;
    flag_parts[2] -= 22356040786590640;
    flag_parts[0] -= 32867094629382943;
    flag_parts[3] ^= 13271716658844936;
    flag_parts[2] -= 8506450816683408;
    flag_parts[3] ^= 24054640919503309;
    flag_parts[0] -= 8047372581470335;
    flag_parts[0] ^= 9770350554125952;
    flag_parts[0] -= 29897809509527184;
    flag_parts[2] += 20369987708823534;
    flag_parts[0] += 31323195149824595;
    flag_parts[1] ^= 16086001967263549;
    flag_parts[1] -= 21663229686219085;
    flag_parts[3] ^= 121544854872314;
    flag_parts[3] += 9521986249151110;
    flag_parts[3] -= 8639316963744315;
    flag_parts[3] ^= 20081290104837563;
    flag_parts[1] -= 16742982847482253;
    flag_parts[0] ^= 24595513239458244;
    flag_parts[0] ^= 1860208297542106;
    flag_parts[2] ^= 1542368855659923;
    flag_parts[2] ^= 25944897283500707;
    flag_parts[2] += 6861925784994005;
    flag_parts[2] -= 7052601394136303;
    flag_parts[0] += 19529197288272137;
    flag_parts[0] ^= 7442221908940086;
    flag_parts[2] += 14354676241038873;
    flag_parts[3] -= 28810235278235150;
    flag_parts[0] += 8503160298573563;
    flag_parts[0] -= 30619100275762695;
    flag_parts[0] += 14596854532323998;
    flag_parts[1] += 35184773501454848;
    flag_parts[0] ^= 27877834010603467;
    flag_parts[2] ^= 26011407072706712;
    flag_parts[2] ^= 5093774338058923;
    flag_parts[2] ^= 34009405319253148;
    flag_parts[3] += 18823334773356498;
    flag_parts[3] ^= 17839564625581509;
    flag_parts[1] += 12607458312059396;
    flag_parts[0] += 25489328907481442;
    flag_parts[0] += 5215796565916634;
    flag_parts[0] -= 6838499563527482;
    flag_parts[3] += 23138890010337240;
    flag_parts[3] += 2961458535315782;
    flag_parts[1] ^= 27886827615889316;
    flag_parts[1] += 19930343090114095;
    flag_parts[3] += 6505788486621165;
}

void flag_check(uint64_t* flag_parts) {
    flag_parts[0] += 33099213913749199;
    flag_parts[1] -= 33606379049096977;
    flag_parts[0] ^= 33424632415901132;
    flag_parts[2] += 33230783476689372;
    flag_parts[0] ^= 24100496928992801;
    flag_parts[0] += 26006159031618073;
    flag_parts[0] ^= 16304179943296;
    flag_parts[2] ^= 8538102968241731;
    flag_parts[3] -= 3765180641415530;
    flag_parts[0] ^= 21469902131485757;
    flag_parts[2] += 19155121920259644;
    flag_parts[3] ^= 16137110564186523;
    flag_parts[0] -= 35843862328676501;
    flag_parts[0] += 15878054118526416;
    flag_parts[0] -= 3087469106162152;
    flag_parts[0] -= 22806453944663012;
    flag_parts[2] ^= 21312081623507634;
    flag_parts[0] ^= 3267854261716804;
    flag_parts[3] ^= 28066195149039876;
    flag_parts[1] += 31782594317701597;
    flag_parts[0] ^= 7942925993761866;
    flag_parts[0] ^= 32116026620024518;
    flag_parts[0] += 3194035947701979;
    flag_parts[1] -= 4044427788725040;
    flag_parts[1] += 19642632986769101;
    flag_parts[1] -= 29930786301043705;
    flag_parts[3] -= 5214209273807658;
    flag_parts[0] += 11215658211388059;
    flag_parts[3] -= 27952612669209286;
    flag_parts[3] += 16934736294712410;
    flag_parts[1] += 13691616892073437;
    flag_parts[2] += 32151826856066121;
    flag_parts[1] += 32062438790181170;
    flag_parts[1] -= 33649086000580867;
    flag_parts[2] -= 17887870323380878;
    flag_parts[2] -= 13631414325138830;
    flag_parts[1] ^= 15488857077364001;
    flag_parts[2] += 5270625192502203;
    flag_parts[1] += 17602613009432930;
    flag_parts[2] -= 17375848675607397;
    flag_parts[3] ^= 9537239046375051;
    flag_parts[3] += 19351426925634354;
    flag_parts[1] += 22328536923605711;
    flag_parts[1] += 13469455667668553;
    flag_parts[1] -= 24223971871247444;
    flag_parts[2] += 13110223907774287;
    flag_parts[3] += 19476414844331035;
    flag_parts[3] -= 1996049762164116;
    flag_parts[1] += 6129616729370320;
    flag_parts[2] ^= 32513078396034605;
    flag_parts[1] ^= 19383800852006163;
    flag_parts[1] -= 20985812031517004;
    flag_parts[2] ^= 11143755398457468;
    flag_parts[0] ^= 35669272188120048;
    flag_parts[2] -= 15942472096146639;
}

bool is_correct(uint64_t* flag_parts) {
    return (flag_parts[0] == 3560058869926410689) && (flag_parts[1] == 7441546026153566949) && (flag_parts[2] == 7090439951776091259) && (flag_parts[3] == 9142337937779711589);
}

int main(int argc, char const *argv[]) {
    char* flag = NULL;
    size_t len = 0;
    size_t bytes_read;

    printf("whats the flag: ");
    bytes_read = getline(&flag, &len, stdin);
    flag[bytes_read - 1] = '\0';
    uint64_t* flag_parts;
    flag_parts = (uint64_t*)flag;
    flag_check(flag_parts);
    flag_check2(flag_parts);
    flag_check3(flag_parts);
    flag_check4(flag_parts);
    if (strlen(flag) != 32 || !is_correct(flag_parts)) {
        puts("nuh uh");
        return 0;
    }
    puts("good job!");
    return 0;
}
