//
//  main.cpp
//  split_fasta with exponentially number of lines per file
//
//  Created by Andrea Ghelfi on 2022/10/31.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

void func_split_fasta(){
    string dir = "/data/";
    ifstream index_file;
    // count the number of fasta sequences;
    string filename1 = dir + "temp_svp/index_line2fasta.txt";
    index_file.open(filename1, ios::in);
    string line_index;
    int num_of_lines = 0;
    if(index_file.is_open()){
        while (getline(index_file, line_index)) {
            num_of_lines = num_of_lines + 1;
        }
    }
    // create output file for index split;
    string output_filename1;
    output_filename1 = dir + "temp_svp/index_split2fasta.txt";
    ofstream output_index(output_filename1);
    // create output file for entry, first_base, last_base;
    string output_filename_bases;
    output_filename_bases = dir + "temp_svp/temp_length_firstlastbases.txt";
    ofstream output_bases(output_filename_bases);
    // open fasta file;
    ifstream fasta_file;
    string filename2 = dir + "temp_svp/oneline.txt";
    fasta_file.open(filename2, ios::in);
    int i = 0;
    int j = 0;
    int n = std::pow(2, j);
    int total = 0;
    
    while (total < num_of_lines) {
        i++;
        string index_i = to_string(i);
        string output_fasta_file, line;
        output_fasta_file = dir + "temp_svp/tmp/file_" + index_i;
        ofstream output_fasta(output_fasta_file);
//        cout << "Begin i = " << i << " j = " << j << " n = " << n << endl;
        for (j = 0; j < n; j++){
            if (fasta_file.is_open()){
                getline(fasta_file, line);
                output_fasta << line << "\n" ;
                size_t delim_pos = 0;
                delim_pos = line.find("%", 0);
                string entry_id = line.substr(1, delim_pos - 1) ;
                output_index << "file_" << index_i << "\t" << entry_id << endl;
//                cout << "file_ = " << entry_id << endl;
                size_t pos_first_base = delim_pos + 1;
                size_t pos_size = line.size();
                size_t pos_last_base = pos_size - 1;
                size_t seq_length = pos_size - (delim_pos + 1);
                string first_base = line.substr(pos_first_base, 1) ;
                string last_base = line.substr(pos_last_base, 1) ;
                output_bases << entry_id << "\t" << seq_length << "\t" << first_base << "\t" << last_base << endl;
            } else {
                cout << filename2;
                cout << ": Cannot open file \n";
            }
        }
        n = round (1.5 * n);
        total = total + j;
//        cout << "End i = " << i << " j = " << j << " n = " << n << " total = " << total << endl;
        if (total + j >= num_of_lines){
            n = num_of_lines - total;
        }
    }
    fasta_file.close();
    index_file.close();
    output_index.close();
    output_bases.close();
}

int main() {
    func_split_fasta();
    return 0;
}
