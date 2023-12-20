//
//  main.cpp
//  oneline_fasta
//
//  Created by Andrea Ghelfi on 2022/10/28.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
//#include <cctype>

using namespace std;

void func_makeoneline(){
    string dir = "/data/";
    ifstream input_files;
    string input_ids = dir + "temp_svp/input_ids.txt";
    
    input_files.open(input_ids, ios::in);
    string filename;

    while(getline(input_files, filename)){
        filename = dir + filename + ".fasta";
        cout << "check_point_01: " << filename << endl;
        ifstream myFile;
        myFile.open(filename, ios::in);//read
        string output_filename2;
        output_filename2 = dir + "temp_svp/index_line2fasta.txt";
        ofstream output_index(output_filename2);
        // start blocks
        int j = 1;
        string output_filename_block;
        output_filename_block = dir + "temp_svp/oneline.txt";
        ofstream output_block(output_filename_block);
        cout << "check_point_02: " << output_filename_block << endl;
        // end blocks
        if(myFile.is_open()){
            string line;
            int i = 0;
            while(getline(myFile, line)){
                output_block << line << "%";
                output_index << "b" << j << line << "\n";
                i++;
                break;
            }
            string fasta_marker;
            while(getline(myFile, line)){
                fasta_marker = line.substr(0,1);
                if(fasta_marker == ">"){
                    if(i < 100){
                        output_block << "\n" ;
                        output_block << line << "%";
                        output_index << "b" << j << line << "\n";
                        i++;
                    } else if (i == 100) {
                        j++;
                        i = 1;
                        output_block << "\n" ;
                        output_block << line << "%";
                        output_index << "b" << j << line << "\n";
                    }
                } else {
                    line.erase(remove(line.begin(), line.end(), '/'), line.end());
                    output_block << line;
                }
            }
            
        myFile.close();
        output_block.close();
        output_index.close();
        } else {
            cout << filename;
            cout << ": Cannot open file \n";
        }
        
    }
    input_files.close();
    
}
int main() {
    func_makeoneline();
    return 0;
}
