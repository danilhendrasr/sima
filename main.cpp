#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

using namespace std;

struct Mahasiswa
{
  char npm[50];
  char nama[50];
  char jurusan[50];
};

int getOption();
int getDataSize(fstream *data);
void displayData(fstream *data);
void updateRecord(fstream *data);
void deleteRecord(fstream *data);
void checkDatabase(fstream *data);
void addStudentData(fstream *data);
void writeData(fstream *data, int posisi, Mahasiswa *inputMahasiswa);
Mahasiswa readData(fstream *data, int posisi);

int main()
{
  fstream data;
  data.open("data.bin", ios::out | ios::in | ios::binary);

  checkDatabase(&data);

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
      cout << "Menambah data mahasiswa\n";
      addStudentData(&data);
      break;
    case READ:
      cout << "\nTampilkan data mahasiswa\n\n";
      displayData(&data);
      break;
    case UPDATE:
      cout << "\nUbah data mahasiswa\n\n";
      cout << "\n=============== Data saat ini ===============\n";
      displayData(&data);
      cout << "=======================================================\n";

      updateRecord(&data);

      cout << "\n=============== Data setelah update ===============\n";
      displayData(&data);
      cout << "=======================================================\n";
      break;
    case DELETE:
      cout << "\nHapus data mahasiswa\n\n";
      cout << "\n=============== Data saat ini ===============\n";
      displayData(&data);
      cout << "=======================================================\n";

      deleteRecord(&data);

      cout << "\n=============== Data setelah penghapusan ===============\n";
      displayData(&data);
      cout << "=======================================================\n";
      break;
    default:
      cout << "\nMenu tidak ada\n";
    }

  labelContinue:
    cout << "\nLakukan operasi lain?(y/N): ";
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

  data.close();
  cout << "Program telah diakhiri\n";
}

int getOption()
{
  int input;

  system("clear");

  cout << "\nProgram CRUD data mahasiswa\n";
  cout << "==============================\n";
  cout << "1. Tambah data mahasiswa\n";
  cout << "2. Tampilkan data mahasiswa\n";
  cout << "3. Ubah data mahasiswa\n";
  cout << "4. Hapus data mahasiswa\n";
  cout << "5. Keluar\n";
  cout << "============================\n";
  cout << "Pilih [1-5]: ";
  cin >> input;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  return input;
}

void checkDatabase(fstream *data)
{
  // Check if database file exists
  if (data->is_open())
  {
    cout << "Database exists\n";
  }
  else
  {
    cout << "Database not found, created a new one\n";
    data->close();
    data->open("data.bin", ios::trunc | ios::out | ios::in | ios::binary);
  }
}

int getDataSize(fstream *data)
{
  int start, end;
  data->seekg(0, ios::beg);
  start = data->tellg();
  data->seekg(0, ios::end);
  end = data->tellg();
  return (end - start) / sizeof(Mahasiswa);
}

Mahasiswa readData(fstream *data, int posisi)
{
  Mahasiswa readMahasiswa;
  data->seekg(posisi * sizeof(Mahasiswa), ios::beg);
  data->read((char *)&readMahasiswa, sizeof(Mahasiswa));
  return readMahasiswa;
}

void addStudentData(fstream *data)
{
  Mahasiswa inputMahasiswa, lastMahasiswa;

  int size = getDataSize(data);

  cout << "Ukuran data: " << size << endl;

  cout << "NPM: ";
  cin.getline(inputMahasiswa.npm, sizeof(inputMahasiswa.npm));
  cout << "Nama: ";
  cin.getline(inputMahasiswa.nama, sizeof(inputMahasiswa.nama));
  cout << "Jurusan: ";
  cin.getline(inputMahasiswa.jurusan, sizeof(inputMahasiswa.jurusan));

  writeData(data, size, &inputMahasiswa);
}

void displayData(fstream *data)
{
  int size = getDataSize(data);
  Mahasiswa currentMahasiswa;

  cout.width(5);
  cout << left << "No.";
  cout.width(15);
  cout << left << "NPM";
  cout.width(30);
  cout << left << "Nama";
  cout.width(30);
  cout << left << "Jurusan" << endl;

  for (int i = 0; i < size; i++)
  {
    currentMahasiswa = readData(data, i);
    cout.width(5);
    cout << left << i + 1;
    cout.width(15);
    cout << left << currentMahasiswa.npm;
    cout.width(30);
    cout << left << currentMahasiswa.nama;
    cout.width(30);
    cout << left << currentMahasiswa.jurusan << endl;
  }
}

void writeData(fstream *data, int posisi, Mahasiswa *inputMahasiswa)
{
  data->seekp(posisi * sizeof(Mahasiswa), ios::beg);
  data->write((char *)inputMahasiswa, sizeof(Mahasiswa));
}

void updateRecord(fstream *data)
{
  int entryNumber;
  Mahasiswa whichMahasiswa;
  int dataCount = getDataSize(data);

  do
  {
    cout << "Pilih nomor entri [1-" << dataCount << "]: ";
    cin >> entryNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (entryNumber > dataCount)
    {
      cout << "Data dengan nomor " << entryNumber << " tidak ditemukan\n";
    }
  } while (entryNumber > dataCount);

  int positionInFile = entryNumber - 1;
  whichMahasiswa = readData(data, positionInFile);

  cout << "\n====== Data saat ini ======\n";
  cout << "NPM: " << whichMahasiswa.npm << endl;
  cout << "Nama: " << whichMahasiswa.nama << endl;
  cout << "Jurusan: " << whichMahasiswa.jurusan << endl;
  cout << "===========================\n";

  cout << "\n====== Masukkan data baru ======\n";
  cout << "NPM: ";
  cin.getline(whichMahasiswa.npm, sizeof(whichMahasiswa.npm));
  cout << "Nama: ";
  cin.getline(whichMahasiswa.nama, sizeof(whichMahasiswa.nama));
  cout << "Jurusan: ";
  cin.getline(whichMahasiswa.jurusan, sizeof(whichMahasiswa.jurusan));

  writeData(data, positionInFile, &whichMahasiswa);
}

void deleteRecord(fstream *data)
{
  int deleteNumber, size, offset;

  Mahasiswa blankMahasiswa, tempMahasiswa;
  fstream temporaryData;
  size = getDataSize(data);

  cout << "Masukkan nomor data yang ingin dihapus [1-" << size << "]: ";
  cin >> deleteNumber;

  writeData(data, deleteNumber - 1, &blankMahasiswa);

  temporaryData.open("temp.bin", ios::trunc | ios::out | ios::in | ios::binary);

  offset = 0;
  for (int i = 0; i < size; i++)
  {
    tempMahasiswa = readData(data, i);

    if (strlen(tempMahasiswa.nama) != 0)
    {
      writeData(&temporaryData, i - offset, &tempMahasiswa);
    }
    else
    {
      offset++;
      cout << "Deleted item\n";
    }
  }

  size = getDataSize(&temporaryData);
  data->close();
  data->open("data.bin", ios::trunc | ios::out | ios::binary);
  data->close();
  data->open("data.bin", ios::out | ios::in | ios::binary);

  for (int i = 0; i < size; i++)
  {
    tempMahasiswa = readData(&temporaryData, i);
    writeData(data, i, &tempMahasiswa);
  }

  temporaryData.close();
  remove("temp.bin");
}