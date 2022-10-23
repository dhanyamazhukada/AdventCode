#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>

class PointInfo {
public:
    PointInfo(int xIn, int yIn, int vX, int vY) : x(xIn), y(yIn), vx(vX), vy(vY) {}
    int getX(int time) const
    {
        return x + (vx*time);
    }
    int getY(int time) const
    {
        return y + (vy*time);
    }
    bool isSame(int xIn, int yIn, int time) const
    {
        bool ret = (getX(time) == xIn) && (getY(time) == yIn);
        return ret;
    }
private:
    int x, y, vx, vy;
};

bool extractPointsInfo(std::string inputString, std::vector<PointInfo>& info)
{
    try {
        size_t linePos = 0;
        do {
            size_t startX = inputString.find_first_of("<", linePos) + 1;

            size_t endX = inputString.find_first_of(",", startX);
            std::string x = inputString.substr(startX, endX - startX);

            size_t startY = endX + 1;
            size_t endY = inputString.find_first_of(">", startY);
            std::string y = inputString.substr(startY, endY - startY);

            size_t startVx = inputString.find_first_of("<", endY) + 1;
            size_t endVX = inputString.find_first_of(",", startVx);
            std::string Vx = inputString.substr(startVx, endVX - startVx);

            size_t startVy = endVX + 1;
            size_t endVy = inputString.find_first_of(">", startVy);
            std::string Vy = inputString.substr(startVy, endVy - startVy);


            info.push_back(PointInfo(std::stoi(x), std::stoi(y), std::stoi(Vx), std::stoi(Vy)));

            if (inputString.find_first_of("position", endVy) == std::string::npos) {
                return true;
            }
            linePos = endVy;
        } while (1);
    }
    catch (...) {
        std::cout << "Extracting points info failed! Check the input string" << std::endl;
        return false;
    }
}

void printPosition(std::vector<PointInfo>& pointsInfo, int time, int xMin, int xMax, int yMin, int yMax)
{
    std::sort(pointsInfo.begin(), pointsInfo.end(), [time] (const PointInfo& p1, const PointInfo& p2) {
                                                        if (p1.getY(time) < p2.getY(time)) {
                                                            return true;
                                                        }
                                                        else if (p1.getY(time) == p2.getY(time)) {
                                                            return p1.getX(time) < p2.getX(time);
                                                        }
                                                        else {
                                                            return false;
                                                        }
                                                    });
    pointsInfo.erase(std::unique(pointsInfo.begin(), pointsInfo.end(), [time](const PointInfo& p1, const PointInfo& p2) {
                                return p1.isSame(p2.getX(time), p2.getY(time), time);
                                }),
                    pointsInfo.end());
    int x, y;
    auto it = pointsInfo.begin();
    for (y = yMin ; y <= yMax; y++ ){
        std::cout << std::endl;
        for(x = xMin; x <= xMax; x++) {
            if (it != std::end(pointsInfo) && it->isSame(x, y, time)) {
                std::cout << "# ";
                it++;
            }
            else {
                std::cout << ". ";
            }
        }
    }
    std::cout << std::endl;
}
int main() {
    using namespace std::chrono_literals;
    std::string inputString = R"(position=<-31684, -53051> velocity=< 3,  5>
position=< 10860,  32026> velocity=<-1, -3>
position=< 42712,  42663> velocity=<-4, -4>
position=<-52978, -10507> velocity=< 5,  1>
position=< 42704,  42656> velocity=<-4, -4>
position=<-42368, -31781> velocity=< 4,  3>
position=< 53391, -53049> velocity=<-5,  5>
position=<-31694, -42409> velocity=< 3,  4>
position=<-52970,  21388> velocity=< 5, -2>
position=<-10433, -21140> velocity=< 1,  2>
position=<-53002, -53044> velocity=< 5,  5>
position=<-42363,  21390> velocity=< 4, -2>
position=<-42355, -42411> velocity=< 4,  4>
position=<-10409, -21143> velocity=< 1,  2>
position=<-10418, -42410> velocity=< 1,  4>
position=<-31714, -31783> velocity=< 3,  3>
position=<-52962, -21149> velocity=< 5,  2>
position=<-31675,  42660> velocity=< 3, -4>
position=< 10802,  32028> velocity=<-1, -3>
position=<-52944, -31778> velocity=< 5,  3>
position=<-42317, -10511> velocity=< 4,  1>
position=< 42744, -42413> velocity=<-4,  4>
position=<-21092,  32023> velocity=< 2, -3>
position=< 32114, -42417> velocity=<-3,  4>
position=<-52985, -21149> velocity=< 5,  2>
position=<-42339,  10762> velocity=< 4, -1>
position=<-21100, -31779> velocity=< 2,  3>
position=< 53386, -21140> velocity=<-5,  2>
position=<-21084, -31776> velocity=< 2,  3>
position=< 42752,  53297> velocity=<-4, -5>
position=<-52982, -21149> velocity=< 5,  2>
position=<-52998, -53051> velocity=< 5,  5>
position=< 53373,  21387> velocity=<-5, -2>
position=< 21495, -42412> velocity=<-2,  4>
position=<-42320,  10762> velocity=< 4, -1>
position=< 42720, -42417> velocity=<-4,  4>
position=<-21100,  42658> velocity=< 2, -4>
position=< 10839,  10761> velocity=<-1, -1>
position=<-10422, -10511> velocity=< 1,  1>
position=< 32071,  10753> velocity=<-3, -1>
position=<-21075,  42664> velocity=< 2, -4>
position=<-52986, -53051> velocity=< 5,  5>
position=< 32130,  21394> velocity=<-3, -2>
position=<-52950, -42408> velocity=< 5,  4>
position=<-52994, -21149> velocity=< 5,  2>
position=<-42360,  21387> velocity=< 4, -2>
position=< 42706,  10753> velocity=<-4, -1>
position=<-52968, -53051> velocity=< 5,  5>
position=<-31721,  53298> velocity=< 3, -5>
position=<-42339, -42408> velocity=< 4,  4>
position=<-52978, -53051> velocity=< 5,  5>
position=<-42328,  10762> velocity=< 4, -1>
position=< 53351,  10759> velocity=<-5, -1>
position=< 32111, -21149> velocity=<-3,  2>
position=< 32123, -31781> velocity=<-3,  3>
position=< 32094, -10515> velocity=<-3,  1>
position=< 10838, -10515> velocity=<-1,  1>
position=< 10858, -42417> velocity=<-1,  4>
position=<-21050,  21396> velocity=< 2, -2>
position=<-10458,  53291> velocity=< 1, -5>
position=<-21099,  21387> velocity=< 2, -2>
position=< 10845, -42408> velocity=<-1,  4>
position=<-31686, -31783> velocity=< 3,  3>
position=<-31702,  21395> velocity=< 3, -2>
position=< 10842,  10756> velocity=<-1, -1>
position=<-10461, -10512> velocity=< 1,  1>
position=<-52949,  32030> velocity=< 5, -3>
position=< 32087, -53047> velocity=<-3,  5>
position=< 42746, -31779> velocity=<-4,  3>
position=< 10831,  21388> velocity=<-1, -2>
position=<-53002,  53291> velocity=< 5, -5>
position=< 21476, -42413> velocity=<-2,  4>
position=<-52989, -31779> velocity=< 5,  3>
position=< 10810, -10515> velocity=<-1,  1>
position=<-42341, -42417> velocity=< 4,  4>
position=<-10461,  32024> velocity=< 1, -3>
position=< 21464,  42658> velocity=<-2, -4>
position=< 21436,  42659> velocity=<-2, -4>
position=<-21084, -10509> velocity=< 2,  1>
position=< 53394,  21388> velocity=<-5, -2>
position=<-52994,  42658> velocity=< 5, -4>
position=< 21477, -21145> velocity=<-2,  2>
position=<-10406,  53295> velocity=< 1, -5>
position=< 53351, -42412> velocity=<-5,  4>
position=<-42336,  32028> velocity=< 4, -3>
position=<-21060,  21394> velocity=< 2, -2>
position=< 21436,  21395> velocity=<-2, -2>
position=< 53391, -42408> velocity=<-5,  4>
position=<-52992, -31779> velocity=< 5,  3>
position=< 42712, -31778> velocity=<-4,  3>
position=< 53378, -53049> velocity=<-5,  5>
position=<-42351,  53289> velocity=< 4, -5>
position=<-42352,  10757> velocity=< 4, -1>
position=< 10853,  10753> velocity=<-1, -1>
position=<-31726,  32030> velocity=< 3, -3>
position=< 10850,  42663> velocity=<-1, -4>
position=< 53351, -42408> velocity=<-5,  4>
position=< 10827, -42411> velocity=<-1,  4>
position=<-21095,  32022> velocity=< 2, -3>
position=<-21083,  32025> velocity=< 2, -3>
position=< 42712, -10509> velocity=<-4,  1>
position=<-10447, -21149> velocity=< 1,  2>
position=< 21444, -31777> velocity=<-2,  3>
position=< 53396, -31779> velocity=<-5,  3>
position=<-31686, -21140> velocity=< 3,  2>
position=<-42312,  53297> velocity=< 4, -5>
position=<-31678,  42655> velocity=< 3, -4>
position=<-31700, -42408> velocity=< 3,  4>
position=< 21436,  32024> velocity=<-2, -3>
position=< 21436,  42655> velocity=<-2, -4>
position=< 42712,  53293> velocity=<-4, -5>
position=<-52942,  42658> velocity=< 5, -4>
position=<-21076,  10761> velocity=< 2, -1>
position=< 53388, -10515> velocity=<-5,  1>
position=<-10462, -31779> velocity=< 1,  3>
position=<-52970,  21393> velocity=< 5, -2>
position=< 53356, -53047> velocity=<-5,  5>
position=<-31694, -42417> velocity=< 3,  4>
position=< 32096, -21149> velocity=<-3,  2>
position=<-52975,  53298> velocity=< 5, -5>
position=< 32081,  21391> velocity=<-3, -2>
position=< 42736, -21148> velocity=<-4,  2>
position=<-31702,  10757> velocity=< 3, -1>
position=< 21481, -42417> velocity=<-2,  4>
position=<-21057,  53289> velocity=< 2, -5>
position=<-52986,  53293> velocity=< 5, -5>
position=< 10815,  10755> velocity=<-1, -1>
position=<-42341, -10515> velocity=< 4,  1>
position=< 21452,  21395> velocity=<-2, -2>
position=< 53346, -10511> velocity=<-5,  1>
position=< 10810,  21389> velocity=<-1, -2>
position=<-10410, -53050> velocity=< 1,  5>
position=<-10464,  42655> velocity=< 1, -4>
position=< 32096, -21149> velocity=<-3,  2>
position=<-52986, -31781> velocity=< 5,  3>
position=< 42736,  42658> velocity=<-4, -4>
position=<-42355, -53050> velocity=< 4,  5>
position=<-10458,  42664> velocity=< 1, -4>
position=< 53389, -21140> velocity=<-5,  2>
position=< 42720,  53290> velocity=<-4, -5>
position=< 53366,  32024> velocity=<-5, -3>
position=< 21436,  21396> velocity=<-2, -2>
position=<-31725, -53047> velocity=< 3,  5>
position=< 21449, -10514> velocity=<-2,  1>
position=< 32121, -10515> velocity=<-3,  1>
position=< 53365, -42413> velocity=<-5,  4>
position=<-52960,  42664> velocity=< 5, -4>
position=< 10842,  10758> velocity=<-1, -1>
position=<-42320, -31775> velocity=< 4,  3>
position=< 10821, -21149> velocity=<-1,  2>
position=< 42765, -10507> velocity=<-4,  1>
position=< 53394,  32029> velocity=<-5, -3>
position=<-42360,  10759> velocity=< 4, -1>
position=<-21096,  21387> velocity=< 2, -2>
position=< 10859, -53049> velocity=<-1,  5>
position=<-21044, -53050> velocity=< 2,  5>
position=<-10434, -53049> velocity=< 1,  5>
position=<-10434, -21147> velocity=< 1,  2>
position=< 21461,  32021> velocity=<-2, -3>
position=< 42733, -10515> velocity=<-4,  1>
position=< 10858, -53043> velocity=<-1,  5>
position=<-42324,  32021> velocity=< 4, -3>
position=< 10835,  21396> velocity=<-1, -2>
position=< 21468, -31778> velocity=<-2,  3>
position=< 10815,  42660> velocity=<-1, -4>
position=<-21057,  10757> velocity=< 2, -1>
position=<-42334, -42408> velocity=< 4,  4>
position=< 21464, -21146> velocity=<-2,  2>
position=<-53002,  10760> velocity=< 5, -1>
position=<-31706, -10515> velocity=< 3,  1>
position=< 53391, -53051> velocity=<-5,  5>
position=< 21476, -42410> velocity=<-2,  4>
position=< 10855, -42415> velocity=<-1,  4>
position=<-42319, -42408> velocity=< 4,  4>
position=<-42360,  32024> velocity=< 4, -3>
position=< 10847,  53298> velocity=<-1, -5>
position=< 42763, -42413> velocity=<-4,  4>
position=< 42712, -31776> velocity=<-4,  3>
position=< 42708,  21391> velocity=<-4, -2>
position=< 32083,  42655> velocity=<-3, -4>
position=< 53398,  53295> velocity=<-5, -5>
position=< 21452, -31782> velocity=<-2,  3>
position=<-10466, -31782> velocity=< 1,  3>
position=< 10861, -10510> velocity=<-1,  1>
position=<-10461,  53291> velocity=< 1, -5>
position=<-10418, -53051> velocity=< 1,  5>
position=< 21476,  10757> velocity=<-2, -1>
position=< 32086, -53043> velocity=<-3,  5>
position=<-31705,  42655> velocity=< 3, -4>
position=<-42335, -21140> velocity=< 4,  2>
position=<-42360, -53046> velocity=< 4,  5>
position=< 10845,  42664> velocity=<-1, -4>
position=<-42308,  10759> velocity=< 4, -1>
position=< 21487, -53051> velocity=<-2,  5>
position=< 42764,  42658> velocity=<-4, -4>
position=<-52989, -21146> velocity=< 5,  2>
position=< 53351, -21142> velocity=<-5,  2>
position=< 21436, -42411> velocity=<-2,  4>
position=<-42360, -31782> velocity=< 4,  3>
position=<-42365,  21391> velocity=< 4, -2>
position=<-31684,  53298> velocity=< 3, -5>
position=< 10838, -10506> velocity=<-1,  1>
position=< 21444, -31778> velocity=<-2,  3>
position=<-42368,  53291> velocity=< 4, -5>
position=< 10802,  42661> velocity=<-1, -4>
position=<-42344, -42410> velocity=< 4,  4>
position=<-31689,  10753> velocity=< 3, -1>
position=< 53399,  32022> velocity=<-5, -3>
position=< 21462,  21387> velocity=<-2, -2>
position=<-53002, -31780> velocity=< 5,  3>
position=< 10829,  21396> velocity=<-1, -2>
position=< 32104,  21396> velocity=<-3, -2>
position=< 32120, -42408> velocity=<-3,  4>
position=<-10458, -31780> velocity=< 1,  3>
position=<-21100,  21393> velocity=< 2, -2>
position=< 42765, -42409> velocity=<-4,  4>
position=< 21465, -42408> velocity=<-2,  4>
position=<-10462,  21387> velocity=< 1, -2>
position=<-31684, -10510> velocity=< 3,  1>
position=< 10802, -21145> velocity=<-1,  2>
position=< 53399,  32030> velocity=<-5, -3>
position=<-21060,  42657> velocity=< 2, -4>
position=<-52986, -31781> velocity=< 5,  3>
position=< 42705,  32025> velocity=<-4, -3>
position=<-31677, -10513> velocity=< 3,  1>
position=<-52962, -42409> velocity=< 5,  4>
position=< 53367,  21389> velocity=<-5, -2>
position=< 10863,  53289> velocity=<-1, -5>
position=< 32110, -53045> velocity=<-3,  5>
position=<-10458, -31774> velocity=< 1,  3>
position=< 21494, -31778> velocity=<-2,  3>
position=<-52958,  42664> velocity=< 5, -4>
position=<-21087, -21141> velocity=< 2,  2>
position=<-10450,  32024> velocity=< 1, -3>
position=< 32098, -21140> velocity=<-3,  2>
position=<-52941, -53043> velocity=< 5,  5>
position=<-42328,  53294> velocity=< 4, -5>
position=< 53378, -21148> velocity=<-5,  2>
position=< 32128,  42659> velocity=<-3, -4>
position=<-42342,  42664> velocity=< 4, -4>
position=<-10422, -31779> velocity=< 1,  3>
position=<-31702,  42662> velocity=< 3, -4>
position=< 21449,  32023> velocity=<-2, -3>
position=< 10862,  10755> velocity=<-1, -1>
position=< 53340, -53047> velocity=<-5,  5>
position=< 21439, -10511> velocity=<-2,  1>
position=< 53387,  32027> velocity=<-5, -3>
position=<-31707, -42408> velocity=< 3,  4>
position=< 42736,  21392> velocity=<-4, -2>
position=<-31690, -10515> velocity=< 3,  1>
position=<-21048, -53051> velocity=< 2,  5>
position=< 10818,  32021> velocity=<-1, -3>
position=< 32103,  10753> velocity=<-3, -1>
position=< 21492,  53289> velocity=<-2, -5>
position=< 32086,  21395> velocity=<-3, -2>
position=<-21082, -10511> velocity=< 2,  1>
position=<-42315, -21140> velocity=< 4,  2>
position=<-31724, -10511> velocity=< 3,  1>
position=< 10826,  32028> velocity=<-1, -3>
position=<-52990,  10757> velocity=< 5, -1>
position=< 42757,  53290> velocity=<-4, -5>
position=<-42307,  42656> velocity=< 4, -4>
position=<-10449, -53051> velocity=< 1,  5>
position=<-10466,  10758> velocity=< 1, -1>
position=<-31708, -10510> velocity=< 3,  1>
position=<-42363, -21147> velocity=< 4,  2>
position=< 53365, -31779> velocity=<-5,  3>
position=< 32070,  42660> velocity=<-3, -4>
position=< 21493, -10512> velocity=<-2,  1>
position=< 21455, -42413> velocity=<-2,  4>
position=<-21065,  21396> velocity=< 2, -2>
position=< 10810,  21394> velocity=<-1, -2>
position=< 53351, -10510> velocity=<-5,  1>
position=< 21488, -42414> velocity=<-2,  4>
position=< 42764,  53296> velocity=<-4, -5>
position=< 42725, -42417> velocity=<-4,  4>
position=< 53366,  42655> velocity=<-5, -4>
position=< 32082,  42659> velocity=<-3, -4>
position=< 53354,  10757> velocity=<-5, -1>
position=< 32086,  21396> velocity=<-3, -2>
position=<-52994,  32025> velocity=< 5, -3>
position=<-42319, -31774> velocity=< 4,  3>
position=<-42360,  32028> velocity=< 4, -3>
position=<-42368, -21144> velocity=< 4,  2>
position=< 21493, -42410> velocity=<-2,  4>
position=<-31700,  10753> velocity=< 3, -1>
position=< 42729, -10506> velocity=<-4,  1>
position=< 21468, -21142> velocity=<-2,  2>
position=< 32131, -31774> velocity=<-3,  3>
position=< 32102,  10758> velocity=<-3, -1>
position=< 32126, -42408> velocity=<-3,  4>
position=<-31682, -31780> velocity=< 3,  3>
position=< 21452,  32022> velocity=<-2, -3>
position=<-42335, -42417> velocity=< 4,  4>
position=<-10409,  32027> velocity=< 1, -3>
position=< 53382, -10511> velocity=<-5,  1>
position=<-21059, -21140> velocity=< 2,  2>
position=<-31684, -21144> velocity=< 3,  2>
position=<-31709, -10515> velocity=< 3,  1>
position=< 32119, -53051> velocity=<-3,  5>
position=< 21449,  21393> velocity=<-2, -2>
position=< 10826,  32030> velocity=<-1, -3>
position=<-21074, -42408> velocity=< 2,  4>
position=< 10814,  53293> velocity=<-1, -5>
position=<-42352,  10759> velocity=< 4, -1>
position=< 10822, -10515> velocity=<-1,  1>
position=< 32110, -31780> velocity=<-3,  3>
position=<-10450, -53045> velocity=< 1,  5>
position=< 32115,  21387> velocity=<-3, -2>
position=< 42723,  42659> velocity=<-4, -4>
position=<-52989, -21149> velocity=< 5,  2>
position=< 42720,  21392> velocity=<-4, -2>
position=<-31716, -10515> velocity=< 3,  1>
position=<-21075,  10762> velocity=< 2, -1>
position=<-52953,  21393> velocity=< 5, -2>
position=<-52997, -31782> velocity=< 5,  3>
position=<-21075,  53295> velocity=< 2, -5>
position=< 42707,  42655> velocity=<-4, -4>
position=<-52986,  21389> velocity=< 5, -2>
position=<-10437, -10515> velocity=< 1,  1>
position=<-52961, -10506> velocity=< 5,  1>
position=<-21040,  10755> velocity=< 2, -1>
position=< 21493,  42657> velocity=<-2, -4>
position=<-31685, -53042> velocity=< 3,  5>
position=< 10844, -53051> velocity=<-1,  5>
position=< 53378, -42411> velocity=<-5,  4>
position=<-31731, -21149> velocity=< 3,  2>
position=<-52989,  10757> velocity=< 5, -1>
position=< 21468, -42414> velocity=<-2,  4>
position=<-31694,  32022> velocity=< 3, -3>
position=<-10425, -53047> velocity=< 1,  5>
position=< 10839,  10754> velocity=<-1, -1>
position=<-31721,  53297> velocity=< 3, -5>
position=< 21456,  53293> velocity=<-2, -5>)";


    std::vector<PointInfo> orgPointsInfo;
    if (extractPointsInfo(inputString, orgPointsInfo)) {
        int time = 0;
        std::vector<PointInfo> pointsInfo;
        do {
            pointsInfo = orgPointsInfo;
            int xMin = std::max_element(pointsInfo.begin(), pointsInfo.end(), [time](const PointInfo& p1, const PointInfo& p2) {
                                                                                    return p1.getX(time) > p2.getX(time);
                                                                                })->getX(time);
            int xMax = std::max_element(pointsInfo.begin(), pointsInfo.end(), [time](const PointInfo& p1, const PointInfo& p2) {
                                                                                    return p1.getX(time) < p2.getX(time);
                                                                                })->getX(time);
            int yMin = std::max_element(pointsInfo.begin(), pointsInfo.end(), [time](const PointInfo& p1, const PointInfo& p2) {
                                                                                    return p1.getY(time) > p2.getY(time);
                                                                                })->getY(time);
            int yMax = std::max_element(pointsInfo.begin(), pointsInfo.end(), [time](const PointInfo& p1, const PointInfo& p2) {
                                                                                    return p1.getY(time) < p2.getY(time);
                                                                                })->getY(time);
            if ( (std::abs(xMax - xMin) < 500) &&  (std::abs(yMax - yMin) < 500)) {
                std::cout << " Print when time is " << time << std::endl;
                std::this_thread::sleep_for(1000ms);
                printPosition(pointsInfo, time, xMin, xMax, yMin, yMax);

            }
            else {
                std::cout << " Skip printing when time = " << time << std::endl;
            }
            time++;
        } while (1);
    }
    return 0;
}
