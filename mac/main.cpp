#include <iostream>
#include <string>
#include <cctype>
#include <stdint.h>
#include <stdlib.h>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

class checkout
{

public:
    string namaPasien;
    char kelas;
    uint8_t lamaInap;
    string penanganan;

    uint32_t biayaInap;
    uint32_t biayaLayanan;
    uint32_t biayaPersalinan;

    uint64_t tunai;
    uint64_t kembalian;

    uint64_t totalBiaya;
    //members function declaration
    checkout();
    void clear();
    void setBiayaKelas();
    void setBiayaPenanganan();
    int checkHadiah();
    void printData();
    void hitungTotalBiaya();
    void biayaKasir(uint64_t);

private:
    string setCommas(uint32_t);
};

checkout::checkout()
{
    clear();
}
void checkout::clear()
{
    namaPasien = " ";
    kelas = '\0';
    biayaInap = 0;
    biayaLayanan = 0;
    lamaInap = 0;
    penanganan = " ";
    biayaPersalinan = 0;
    totalBiaya = 0;
    tunai = 0;
    kembalian = 0;
}
int checkout::checkHadiah()
{
    return lamaInap > 5 ? 1 : 0;
}

void checkout::setBiayaKelas()
{
    biayaInap = (kelas == 'A') ? 300000 : 200000;
    biayaLayanan = (kelas == 'A') ? 100000 : 70000;
}

void checkout::setBiayaPenanganan()
{
    biayaPersalinan = !penanganan.compare("JASA DOKTER") ? 1000000 : !penanganan.compare("JASA BIDAN") ? 750000
                                                                                                       : 0;
}

void checkout::biayaKasir(uint64_t t)
{
    tunai = t;
    kembalian = tunai - totalBiaya;
}

void checkout::printData()

{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "      KLINIK PERSALINAN 'MAWAR' CHECKOUT APLIKASI      " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    cout << "nama pasien\t\t: " << namaPasien << endl;
    cout << "kelas\t\t\t: " << kelas << endl;
    cout << "penanganan\t\t: " << penanganan << endl;
    cout << " " << endl;
    cout << "lama inap\t\t: " << (unsigned int)(lamaInap) << endl;
    cout << "biaya inap\t\t: " << setCommas(biayaInap) << endl;
    cout << "biaya layanan\t\t: " << setCommas(biayaLayanan) << endl;

    cout << "biaya persalinan\t: " << setCommas(biayaPersalinan) << endl;
    cout << " " << endl;
    cout << "                     ------------------------------- " << endl;
    cout << " " << endl;
    cout << "                      BIAYA\t: " << setCommas(totalBiaya) << endl;
    cout << "                      TUNAI\t: " << setCommas(tunai) << endl;
    cout << "                      KEMBALIAN\t: " << setCommas(kembalian) << endl;
    if (checkHadiah())
    {
        cout << " " << endl;
        cout << "                         HADIAH                        " << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "|        *** SOUVENIR PERLENGKAPAN BAYI ***           |" << endl;
        cout << "-------------------------------------------------------" << endl;
    }
    cout << " " << endl;
    cout << "-------------------------------------------------------" << endl;
}

void checkout::hitungTotalBiaya()
{
    totalBiaya = (unsigned int)(lamaInap)*biayaInap + biayaLayanan + biayaPersalinan;
}

string checkout::setCommas(uint32_t value)
{
    // string s = std::to_string(value);
    stringstream ss;
    ss << value;
    string s = ss.str();
    int n = s.length() - 3;
    while (n > 0)
    {
        s.insert(n, ",");
        n -= 3;
    }
    // s.insert(0, "Rp. ");
    return s;
}

void displayMenu()
{
    system("clear");
    const char menu[12][100] = {
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
        "      KLINIK PERSALINAN 'MAWAR' CHECKOUT APLIKASI      ",
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
        "KELAS A",
        "BIAYA INAP : Rp. 300.000, BIAYA PERAWATAN : Rp. 100.000",
        "KELAS B",
        "BIAYA INAP : Rp. 200.000, BIAYA PERAWATAN : Rp. 70.000",
        "-------------------------------------------------------",
        "JENIS PENANGANAN",
        "JASA DOKTER : Rp. 1.000.000",
        "JASA BIDAN  : Rp. 750.000",
        "-------------------------------------------------------",
    };

    for (uint8_t col = 0; col < 12; col++)
    {
        for (uint8_t row = 0; row < 100; row++)
        {
            cout << menu[col][row];
        }
        cout << endl;
    }
}

void displayCommandMenu()
{
    const char menu[6][100] = {
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
        "1. input data                     4. lihat menu        ",
        "2. hitung biaya                   5. lembar baru       ",
        "3. biaya kasir",
        "                                  x : keluar           ",
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
    };
    for (uint8_t col = 0; col < 6; col++)
    {
        for (uint8_t row = 0; row < 100; row++)
        {
            cout << menu[col][row];
        }
        cout << endl;
    }
}

checkout inputPatientData(checkout co_)
{

    string input;
    const char inputType[6][100] = {
        "",
        "masukan nama pasien : ",
        "masukan jenis kelas : ",
        "masukan total lama inap : ",
        "masukan jenis penanganan : ",
        "pastikan semua data benar? Y/n ",
    };

    for (uint8_t toggle = 1; toggle <= 5; toggle++)
    {

        displayMenu();
        cout << "-------------------------------------------------------" << endl;
        cout << "nama pasien\t: " << co_.namaPasien << endl;
        cout << "kelas\t\t: " << co_.kelas << endl;
        cout << "lama inap\t: " << (unsigned int)(co_.lamaInap) << endl;
        cout << "penanganan\t: " << co_.penanganan << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "z:sebelum   c:setelah               x:simpan & kembali " << endl;
        cout << "-------------------------------------------------------" << endl;

        cout << (unsigned int)toggle
             << ". ";

        for (uint8_t row = 0; row < 100; row++)
        {
            cout << inputType[toggle][row];
        }

        //input data
        cout << "\n";
        cin.clear();
        getline(cin, input);
        boost::algorithm::to_upper(input);
        //check for command in input
        if (!input.compare("X"))
        {
            break;
        }
        if (!input.compare("Z"))
        {

            toggle = toggle == 1 ? 0 : toggle - 2;
        }
        if (!input.compare("C"))
        {
            continue;
        }
        if (input.compare("Z") && input.compare("C"))
        {
            switch (toggle)
            {
            case 1:
                co_.namaPasien = input;
                break;
            case 2:

                if (input[0] == 'A' || input[0] == 'B')
                {
                    co_.kelas = input[0];
                    co_.setBiayaKelas();
                }
                else
                    toggle--;
                break;
            case 3:
            {
                stringstream s(input);
                s.exceptions(ios::failbit);
                try
                {
                    // co_.lamaInap = stoi(input);

                    int buff;
                    s >> buff;
                    co_.lamaInap = buff;
                }
                catch (const exception &e)
                {
                    toggle--;
                }

                break;
            }
            case 4:
                if (!input.compare("JASA DOKTER") || !input.compare("JASA BIDAN"))
                {
                    co_.penanganan = input;
                    co_.setBiayaPenanganan();
                }
                else
                    toggle--;
                break;

            case 5:
                if (input[0] == 'N')

                    toggle = 0;

                else if (input[0] == 'Y')
                    toggle = toggle;
                else
                    toggle--;
                break;
            };
        }
    }

    return co_;
}

int main()
{

    uint8_t input;
    checkout co;
    for (;;)
    {
        system("clear");
        co.printData();
        displayCommandMenu();

        cout << "masukan nomor menu" << endl;
        cin >> input;
        cin.clear();
        cin.ignore();

        switch (input)
        {
        case '1':
            co = inputPatientData(co);
            break;
        case '2':
            co.hitungTotalBiaya();
            break;
        case '3':
            uint64_t inputUang;
            cout << "masukan jumlah pembayaran : " << endl;
            cin >> inputUang;
            cin.clear();
            cin.ignore();
            if (inputUang < co.totalBiaya)
            {
                cout << "jumlah tunai kurang" << endl;
                cout << "tekan enter untuk melanjutkan" << endl;
                cin.get();
            }
            else
                co.biayaKasir(inputUang);
            break;
        case '4':
            displayMenu();
            cout << "tekan enter untuk melanjutkan" << endl;
            cin.get();
            break;
        case '5':
            co.clear();
            break;
        }
        if (tolower(input) == 'x')
            break;
    }

    cout << "..." << endl;
    cout << "menutup aplikasi" << endl;

    return 0;
}