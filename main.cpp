#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>

using namespace std;

struct Mahasiswa
{
  string npm;
  string nama;
  string jurusan;
};

int getOption();
void checkDatabase(fstream &data);
int getDataSize(fstream &data);
Mahasiswa readData(fstream &data, int posisi);
void addStudentData(fstream &data);
void writeData(fstream &data, Mahasiswa &inputMahasiswa);
void displayData(fstream &data);

int main()
{

  fstream data;
  data.open("data.txt", ios::out | ios::in | ios::app);

  checkDatabase(data);

  int userMenuChoice = getOption();

  enum option
  {
    CREATE = 1,
    READ,
    UPDATE,
    DELETE,
    EXIT
  };

  char isContinue;
  while (userMenuChoice != EXIT)
  {
    switch (userMenuChoice)
    {
    case CREATE:
      cout << "Menambah data mahasiswa" << endl;
      addStudentData(data);
      break;
    case READ:
      cout << "Tampilkan data mahasiswa" << endl;
      displayData(data);
      break;
    case UPDATE:
      cout << "Ubah data mahasiswa" << endl;
      break;
    case DELETE:
      cout << "Hapus data mahasiswa" << endl;
    default:
      cout << "Menu tidak ada" << endl;
    }

  labelContinue:
    cout << "Lanjutkan?(y/N): ";
    cin >> isContinue;
    bool isContinueYes = isContinue == 'y' || isContinue == 'Y';
    bool isContinueNo = isContinue == 'n' || isContinue == 'N';

    if (isContinueYes)
    {
      userMenuChoice = getOption();
    }
    else if (isContinueNo)
    {
      break;
    }
    else
    {
      goto labelContinue;
    }
  }

  cout << "Program telah diakhiri";
}

int getOption()
{
  int input;

  system("clear");

  cout << "\nProgram CRUD data mahasiswa" << endl;
  cout << "==============================" << endl;
  cout << "1. Tambah data mahasiswa" << endl;
  cout << "2. Tampilkan data mahasiswa" << endl;
  cout << "3. Ubah data mahasiswa" << endl;
  cout << "4. Hapus data mahasiswa" << endl;
  cout << "5. Keluar" << endl;
  cout << "============================" << endl;
  cout << "Pilih [1-5]: ";
  cin >> input;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  return input;
}

void checkDatabase(fstream &data)
{
  // Check if database file exists
  if (data.is_open())
  {
    cout << "Database exists" << endl;
  }
  else
  {
    cout << "Database not found, created a new one" << endl;
    data.close();
    data.open("data.txt", ios::trunc | ios::out | ios::in | ios::binary);
  }
}

int getDataSize(fstream &data)
{
  int start, end;
  data.seekg(0, ios::beg);
  start = data.tellg();
  data.seekg(0, ios::end);
  end = data.tellg();
  return (end - start) / sizeof(Mahasiswa);
}

Mahasiswa readData(fstream &data, int posisi)
{
  Mahasiswa readMahasiswa;
  data.seekg(posisi * sizeof(Mahasiswa), ios::beg);
  data.read((char *)&readMahasiswa, sizeof(Mahasiswa));
  return readMahasiswa;
}

void addStudentData(fstream &data)
{
  Mahasiswa inputMahasiswa, lastMahasiswa;

  int size = getDataSize(data);

  cout << "Ukuran data: " << size << endl;

  cout << "NPM: ";
  getline(cin, inputMahasiswa.npm);
  cout << "Nama: ";
  getline(cin, inputMahasiswa.nama);
  cout << "Jurusan: ";
  getline(cin, inputMahasiswa.jurusan);

  writeData(data, inputMahasiswa);
}

void displayData(fstream &data)
{
  int size = getDataSize(data);
  Mahasiswa currentMahasiswa;
  cout << "No.\tNPM\tNama\tJurusan" << endl;
  for (int i = 0; i < size; i++)
  {
    currentMahasiswa = readData(data, i);
    cout << i + 1 << "\t";
    cout << currentMahasiswa.npm << "\t";
    cout << currentMahasiswa.nama << "\t";
    cout << currentMahasiswa.jurusan << endl;
  }
}

void writeData(fstream &data, Mahasiswa &inputMahasiswa)
{
  data.write((char *)&inputMahasiswa, sizeof(Mahasiswa));
}