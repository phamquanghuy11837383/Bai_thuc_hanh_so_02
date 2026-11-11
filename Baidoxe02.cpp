
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;
class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg) {
        ma_xe = ma;
        loai_xe = loai;
        gio_vao = gio;
        tg_do = tg;
        phi_do = tinh_phi();
    }

    int lay_ma_xe() const {
        return ma_xe;
    }

    string lay_loai_xe() const {
        return loai_xe;
    }

    void dat_ma_xe(int ma) {
        ma_xe = ma;
    }

    void dat_loai_xe(string loai) {
        loai_xe = loai;
    }

    double tinh_phi() const {
        double gia;

        if (loai_xe == "Car")
            gia = 6.0;
        else if (loai_xe == "Motorcycle")
            gia = 4.0;
        else
            gia = 2.0;

        bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) ||
                        (gio_vao >= 15 && gio_vao <= 18);

        double tong = 0;

        for (int h = 0; h < tg_do; h++) {
            if (h < 2)
                tong += gia * (cao_diem ? 1.30 : 0.95);
            else
                tong += gia * 0.90;
        }

        return tong;
    }

    void hien_thi() const {
        cout << "ID: " << ma_xe
             << " | " << loai_xe
             << " | " << gio_vao << "h"
             << " | " << tg_do << "h"
             << " | Phi: $" << fixed << setprecision(2)
             << tinh_phi() << endl;
    }
};

class bai_xe {
private:
    static const int MAX_VEHICLES = 3;

    int ma_bai;
    char kich_thuoc;
    phuong_tien vehicles[MAX_VEHICLES];
    int currentVehicleCount;

public:
    bai_xe() {
        ma_bai = 0;
        kich_thuoc = 'S';
        currentVehicleCount = 0;
    }

    bai_xe(int ma, char kt) {
        ma_bai = ma;
        kich_thuoc = kt;
        currentVehicleCount = 0;
    }

    int lay_ma() const {
        return ma_bai;
    }

    int suc_chua() const {
        if (kich_thuoc == 'S') return 1;
        if (kich_thuoc == 'M') return 2;
        return 3;
    }

    bool isFull() const {
        return currentVehicleCount >= suc_chua();
    }

    bool them(phuong_tien v) {
        if (isFull())
            return false;

        vehicles[currentVehicleCount] = v;
        currentVehicleCount++;

        return true;
    }

    int findVehicleIndex(int ma_xe) const {
        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i].lay_ma_xe() == ma_xe)
                return i;
        }

        return -1;
    }

    bool xoa(int ma_xe) {
        int vt = findVehicleIndex(ma_xe);

        if (vt == -1)
            return false;

        for (int i = vt; i < currentVehicleCount - 1; i++) {
            vehicles[i] = vehicles[i + 1];
        }

        currentVehicleCount--;

        return true;
    }

    void hien_thi() const {
        cout << "\nBai " << ma_bai
             << " [" << kich_thuoc << "] "
             << currentVehicleCount << "/" << suc_chua()
             << " xe" << endl;

        for (int i = 0; i < currentVehicleCount; i++) {
            vehicles[i].hien_thi();
        }
    }

    bool co_loai(string loai, int& dem, double& tong) const {
        dem = 0;
        tong = 0;

        for (int i = 0; i < currentVehicleCount; i++) {
            if (vehicles[i].lay_loai_xe() == loai) {
                dem++;
                tong += vehicles[i].tinh_phi();
            }
        }

        return dem > 0;
    }
};

class SystemInterface {
private:
    static const int MAX_LOTS = 10;

    bai_xe parkingLots[MAX_LOTS];
    int currentLotCount;

public:
    SystemInterface() {
        currentLotCount = 0;
    }

    bool isParkIDExists(int ma) const {
        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i].lay_ma() == ma)
                return true;
        }

        return false;
    }

    bool isVehicleIDExists(int ma) const {
        for (int i = 0; i < currentLotCount; i++) {
            if (parkingLots[i].findVehicleIndex(ma) != -1)
                return true;
        }

        return false;
    }

    int generateRandomID() {
        return rand() % 90000 + 10000;
    }

    void runMenu() {
        int chon;

        while (true) {
            cout << "\n===== QUAN LY BAI DO XE =====\n";
            cout << "1. Tao bai do\n";
            cout << "2. Them xe\n";
            cout << "3. Xoa bai do\n";
            cout << "4. Lay xe ra\n";
            cout << "5. Hien thi tat ca bai do\n";
            cout << "6. Hien thi xe theo bai\n";
            cout << "7. Liet ke xe theo loai\n";
            cout << "8. Bao cao phi trung binh\n";
            cout << "9. Thoat\n";
            cout << "Chon: ";

            chon = nhapSo();

            if (chon == 1) {
                if (currentLotCount >= MAX_LOTS) {
                    cout << "Da du 10 bai do!\n";
                    continue;
                }

                int ma;
                char kt;

                cout << "Ma bai: ";
                ma = nhapSo();

                if (isParkIDExists(ma)) {
                    cout << "Ma bai bi trung! Tu dong tao ma moi.\n";

                    do {
                        ma = generateRandomID();
                    } while (isParkIDExists(ma));
                }

                do {
                    cout << "Kich thuoc (S/M/L): ";
                    cin >> kt;

                    if (kt >= 'a' && kt <= 'z')
                        kt = kt - 32;

                    if (kt != 'S' && kt != 'M' && kt != 'L')
                        cout << "Kich thuoc khong hop le!\n";

                } while (kt != 'S' && kt != 'M' && kt != 'L');

                parkingLots[currentLotCount] = bai_xe(ma, kt);
                currentLotCount++;

                cout << "Da tao bai " << ma << "\n";
            }

            else if (chon == 2) {
                if (currentLotCount == 0) {
                    cout << "Chua co bai do nao!\n";
                    continue;
                }

                int ma, gio, tg;
                string loai;

                cout << "Ma xe: ";
                ma = nhapSo();

                if (isVehicleIDExists(ma)) {
                    cout << "Ma xe bi trung! Tu dong tao ma moi.\n";

                    do {
                        ma = generateRandomID();
                    } while (isVehicleIDExists(ma));
                }

                do {
                    cout << "Loai (Car/Motorcycle/Bicycle): ";
                    cin >> loai;

                    if (loai != "Car" &&
                        loai != "Motorcycle" &&
                        loai != "Bicycle") {
                        cout << "Loai xe khong hop le!\n";
                    }

                } while (loai != "Car" &&
                         loai != "Motorcycle" &&
                         loai != "Bicycle");

                do {
                    cout << "Gio vao (0-23): ";
                    gio = nhapSo();

                    if (gio < 0 || gio > 23)
                        cout << "Gio khong hop le!\n";

                } while (gio < 0 || gio > 23);

                do {
                    cout << "Thoi luong (1-23): ";
                    tg = nhapSo();

                    if (tg < 1 || tg > 23)
                        cout << "Thoi luong khong hop le!\n";

                } while (tg < 1 || tg > 23);

                phuong_tien v(ma, loai, gio, tg);

                bool ok = false;

                for (int i = 0; i < currentLotCount; i++) {
                    if (parkingLots[i].them(v)) {
                        cout << "Da them xe " << ma
                             << " vao bai " << parkingLots[i].lay_ma()
                             << " | Phi: $" << fixed << setprecision(2)
                             << v.tinh_phi() << endl;

                        ok = true;
                        break;
                    }
                }

                if (!ok)
                    cout << "Tat ca bai do da day!\n";
            }

            else if (chon == 3) {
                int ma;

                cout << "Ma bai can xoa: ";
                ma = nhapSo();

                int vt = -1;

                for (int i = 0; i < currentLotCount; i++) {
                    if (parkingLots[i].lay_ma() == ma) {
                        vt = i;
                        break;
                    }
                }

                if (vt == -1) {
                    cout << "Khong tim thay bai do!\n";
                }
                else {
                    for (int i = vt; i < currentLotCount - 1; i++) {
                        parkingLots[i] = parkingLots[i + 1];
                    }

                    currentLotCount--;

                    cout << "Da xoa bai " << ma << "\n";
                }
            }

            else if (chon == 4) {
                int ma;

                cout << "Ma xe can lay ra: ";
                ma = nhapSo();

                bool ok = false;

                for (int i = 0; i < currentLotCount; i++) {
                    if (parkingLots[i].xoa(ma)) {
                        cout << "Da lay xe " << ma << " ra khoi bai "
                             << parkingLots[i].lay_ma() << "\n";

                        ok = true;
                        break;
                    }
                }

                if (!ok)
                    cout << "Khong tim thay xe!\n";
            }

            else if (chon == 5) {
                if (currentLotCount == 0) {
                    cout << "Chua co bai do nao!\n";
                }

                for (int i = 0; i < currentLotCount; i++) {
                    parkingLots[i].hien_thi();
                }
            }

            else if (chon == 6) {
                int ma;

                cout << "Ma bai: ";
                ma = nhapSo();

                bool ok = false;

                for (int i = 0; i < currentLotCount; i++) {
                    if (parkingLots[i].lay_ma() == ma) {
                        parkingLots[i].hien_thi();
                        ok = true;
                        break;
                    }
                }

                if (!ok)
                    cout << "Khong tim thay bai do!\n";
            }

            else if (chon == 7) {
                string loai;

                cout << "Loai xe: ";
                cin >> loai;

                bool ok = false;

                for (int i = 0; i < currentLotCount; i++) {
                    int dem;
                    double tong;

                    if (parkingLots[i].co_loai(loai, dem, tong)) {
                        parkingLots[i].hien_thi();
                        ok = true;
                    }
                }

                if (!ok)
                    cout << "Khong tim thay xe thuoc loai nay!\n";
            }

            else if (chon == 8) {
                string loai_arr[3] = {
                    "Car", "Motorcycle", "Bicycle"
                };

                for (int t = 0; t < 3; t++) {
                    int demTong = 0;
                    double phiTong = 0;

                    cout << "\nLoai xe: " << loai_arr[t] << endl;

                    for (int i = 0; i < currentLotCount; i++) {
                        int dem;
                        double tong;

                        parkingLots[i].co_loai(loai_arr[t], dem, tong);

                        if (dem > 0) {
                            cout << "Bai " << parkingLots[i].lay_ma()
                                 << ": " << dem << " xe | TB: $"
                                 << fixed << setprecision(2)
                                 << tong / dem << endl;
                        }

                        demTong += dem;
                        phiTong += tong;
                    }

                    if (demTong == 0) {
                        cout << "Khong co xe!\n";
                    }
                    else {
                        cout << "Toan he thong: " << demTong
                             << " xe | TB: $"
                             << fixed << setprecision(2)
                             << phiTong / demTong << endl;
                    }
                }
            }

            else if (chon == 9) {
                cout << "Thoat chuong trinh!\n";
                break;
            }

            else {
                cout << "Lua chon khong hop le!\n";
            }
        }
    }
};

int main() {
    srand(time(0));

    SystemInterface sys;
    sys.runMenu();

    return 0;
}

