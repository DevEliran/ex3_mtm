//#include "ParkingLotTypes.h"
//#include "Time.h"
//#include "ParkingLotPrinter.h"
//#include "ParkingLot.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <map>
//#include <limits>
//
//using std::istream;
//using std::ifstream;
//using std::string;
//using std::cout;
//using std::cin;
//using std::cerr;
//using std::endl;
//using std::map;
//
//using namespace ParkingLotUtils;
//using namespace MtmParkingLot;
//
//static istream& openInputStream(int argc, char* argv[]) {
//    if (argc == 2) {
//        try {
//            return *(new ifstream(argv[1]));
//        }
//        catch (const ifstream::failure& e) {
//            cerr << "Error reading input file!";
//            exit(1);
//        }
//    }
//    return cin;
//}
//
//static void closeInputStream(istream& is) {
//    if (&is == &cin) {
//        return;
//    }
//    static_cast<ifstream&>(is).close();
//    delete &is;
//}
//
//static void handleInputError(istream& inputStream, string errorMsg) {
//    cerr << "Error: " << errorMsg << endl;
//    inputStream.clear();
//    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//}
//
//static VehicleType vehicleStrToVehicleType(string vehicleTypeStr) {
//    static map<string, VehicleType> vehicleTypes = { {"Motorbike", VehicleType::MOTORBIKE},
//                                                     {"Handicapped", VehicleType::HANDICAPPED},
//                                                     {"Car", VehicleType::CAR} };
//    return vehicleTypes.at(vehicleTypeStr);
//}
//
//static void processEnterCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
//    LicensePlate inputLicensePlate;
//    string inputVehicleStr;
//    inputStream >> inputVehicleStr >> inputLicensePlate;
//    if (inputStream.fail()) {
//        handleInputError(inputStream, "invalid input to ENTER command! Usage: ENTER <Vehicle Type> <licensePlate>");
//    }
//    try {
//        parkingLot.enterParking(vehicleStrToVehicleType(inputVehicleStr), inputLicensePlate, currentTime);
//    }
//    catch (std::exception& e) {
//        handleInputError(inputStream, "unrecognized vehicle!");
//    }
//}
//
//static void processExitCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
//    LicensePlate inputLicensePlate;
//    inputStream >> inputLicensePlate;
//    parkingLot.exitParking(inputLicensePlate, currentTime);
//}
//
//static void processPrintCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
//    cout << parkingLot;
//}
//
//static void processPassCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
//    int mins;
//    inputStream >> mins;
//    if (inputStream.fail() || mins < 0) {
//        handleInputError(inputStream, "invalid input to PASS_TIME command! Usage: PASS_TIME <# of mins>");
//        return;
//    }
//    currentTime += mins;
//    cout << "Current time: " << currentTime << endl;
//}
//
//static void processInspectCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
//    parkingLot.inspectParkingLot(currentTime);
//}
//
//static void processInput(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
//    typedef void (*CmdFunction)(istream&, ParkingLot&, Time&);
//    static map<string, CmdFunction> cmdMap = {{"ENTER", processEnterCmd},
//                                              {"EXIT", processExitCmd},
//                                              {"PRINT", processPrintCmd},
//                                              {"PASS_TIME", processPassCmd},
//                                              {"INSPECT", processInspectCmd}};
//    cout << "Enter commands:" << endl;
//    string cmd;
//    while (inputStream >> cmd) {
//        try {
//            CmdFunction cmdFunc = cmdMap.at(cmd);
//            cmdFunc(inputStream, parkingLot, currentTime);
//            inputStream.clear();
//            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        }
//        catch (std::out_of_range& e) {
//            handleInputError(inputStream, "unrecognized command!");
//        }
//    }
//}
//
//static void getParkingSizes(istream& inputStream, unsigned int parkingSizes[]) {
//    int i = 0;
//    while( i < VehicleType::LAST - VehicleType::FIRST + 1) {
//        VehicleType vehicleType = static_cast<VehicleType>(i);
//        cout << "Enter parking size for " << vehicleTypeToString(vehicleType) << ":" << endl;
//        int inputNum;
//        inputStream >> inputNum;
//        if (inputStream.fail() || inputNum < 0) {
//            handleInputError(inputStream, "Invalid size!");
//        }
//        else {
//            parkingSizes[i] = inputNum;
//            i++;
//        }
//    }
//}
//
//int main(int argc, char* argv[]) {
//    if (argc != 1 && argc != 2) {
//        cout << "Usage: " << argv[0] << " [inputFile]" << endl;
//        return 1;
//    }
//    istream& inputStream = openInputStream(argc, argv);
//    unsigned int parkingSizes[VehicleType::LAST-VehicleType::FIRST+1];
//    getParkingSizes(inputStream, parkingSizes);
//    Time currentTime = Time();
//    ParkingLot parkingLot(parkingSizes);
//    processInput(inputStream, parkingLot, currentTime);
//    closeInputStream(inputStream);
//    return 0;
//}


#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingLotPrinter.h"
#include "ParkingLot.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <limits>

using std::istream;
using std::ifstream;
using std::string;
using std::istringstream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::map;

using namespace ParkingLotUtils;
using namespace MtmParkingLot;

static istream& openInputStream(int argc, char* argv[]) {
    if (argc == 2) {
        try {
            return *(new istringstream(argv[1]));
        }
        catch (const ifstream::failure& e) {
            cerr << "Error reading input file!";
            exit(1);
        }
    }
    return cin;
}

static void closeInputStream(istream& is) {
    if (&is == &cin) {
        return;
    }
    delete &is;
}

static void handleInputError(istream& inputStream, string errorMsg) {
    cerr << "Error: " << errorMsg << endl;
    inputStream.clear();
    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static VehicleType vehicleStrToVehicleType(string vehicleTypeStr) {
    static map<string, VehicleType> vehicleTypes = { {"Motorbike", VehicleType::MOTORBIKE},
                                                     {"Handicapped", VehicleType::HANDICAPPED},
                                                     {"Car", VehicleType::CAR} };
    return vehicleTypes.at(vehicleTypeStr);
}

static void processEnterCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
    LicensePlate inputLicensePlate;
    string inputVehicleStr;
    inputStream >> inputVehicleStr >> inputLicensePlate;
    if (inputStream.fail()) {
        handleInputError(inputStream, "invalid input to ENTER command! Usage: ENTER <Vehicle Type> <licensePlate>");
    }
    try {
        parkingLot.enterParking(vehicleStrToVehicleType(inputVehicleStr), inputLicensePlate, currentTime);
    }
    catch (std::exception& e) {
        handleInputError(inputStream, "unrecognized vehicle!");
    }
}

static void processExitCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
    LicensePlate inputLicensePlate;
    inputStream >> inputLicensePlate;
    parkingLot.exitParking(inputLicensePlate, currentTime);
}

static void processPrintCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
    cout << parkingLot;
}

static void processPassCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
    int mins;
    inputStream >> mins;
    if (inputStream.fail() || mins < 0) {
        handleInputError(inputStream, "invalid input to PASS_TIME command! Usage: PASS_TIME <# of mins>");
        return;
    }
    currentTime += mins;
    cout << "Current time: " << currentTime << endl;
}

static void processInspectCmd(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
    parkingLot.inspectParkingLot(currentTime);
}

static void processInput(istream& inputStream, ParkingLot& parkingLot, Time& currentTime) {
    typedef void (*CmdFunction)(istream&, ParkingLot&, Time&);
    static map<string, CmdFunction> cmdMap = {{"ENTER", processEnterCmd},
                                              {"EXIT", processExitCmd},
                                              {"PRINT", processPrintCmd},
                                              {"PASS_TIME", processPassCmd},
                                              {"INSPECT", processInspectCmd}};
    cout << "Enter commands:" << endl;
    string cmd;
    while (inputStream >> cmd && cmd!="STOP") {
        try {
            CmdFunction cmdFunc = cmdMap.at(cmd);
            cmdFunc(inputStream, parkingLot, currentTime);
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (std::out_of_range& e) {
            handleInputError(inputStream, "unrecognized command!");
        }
    }
    inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void getParkingSizes(istream& inputStream, unsigned int parkingSizes[]) {
    int i = 0;
    while( i < VehicleType::LAST - VehicleType::FIRST + 1) {
        VehicleType vehicleType = static_cast<VehicleType>(i);
        cout << "Enter parking size for " << vehicleTypeToString(vehicleType) << ":" << endl;
        int inputNum;
        inputStream >> inputNum;
        if (inputStream.fail() || inputNum < 0) {
            handleInputError(inputStream, "Invalid size!");
            break;
        }
        else {
            parkingSizes[i] = inputNum;
            i++;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 1 && argc != 2) {
        cout << "Usage: " << argv[0] << " [inputFile]" << endl;
        return 1;
    }
    istream& inputStream = openInputStream(argc, argv);
    while (!inputStream.eof() && !(inputStream.peek()==-1)) {
        if (inputStream.eof() || inputStream.peek()==-1){
            cerr << inputStream.eof() << endl;
            break;
        }
        unsigned int parkingSizes[VehicleType::LAST - VehicleType::FIRST + 1];
        getParkingSizes(inputStream, parkingSizes);
        Time currentTime = Time();
        ParkingLot parkingLot(parkingSizes);
        processInput(inputStream, parkingLot, currentTime);
    }
    closeInputStream(inputStream);
    return 0;
}