#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <variant>
#include <fstream>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <algorithm>
#include <map>
#include <regex>
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/filepicker.h>
#include <wx/spinctrl.h>
#include <wx/listctrl.h>

using namespace std;

// adapted from https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
// Ben Gorman Reading And Writing CSV Files With C++

class csv
{
    private:
        string fileName;
        map<string, vector<variant<int, string, float> > > output;
    public:
        csv();
        csv(string f): fileName(f+".csv"){};

        string trim(const string &s)
        {
            string pass1 = regex_replace(s, regex("^\\s+"), "");
            return regex_replace(pass1, regex("\\s+$"), "");
        }
        
        //Vector that pairs each column to a vector of values
        void write(map<string, vector<variant<int, string, float> > > table)
        {
            ofstream csvFile(fileName.c_str());

            int j = 0;
            vector<string> columns; 

            for(const auto &[key, values] : table)
            {
                string columnName = key;

                columns.push_back(columnName);

                csvFile << key;

                if(j != table.size() - 1) csvFile << ",";

                j++;
            }
            
            csvFile << '\n';

            for(int row = 0; row != table[columns[0]].size(); row++)
            {
                for(string col : columns)
                {
                    variant<int, string, float> cell = table[col][row];

                    try
                    {
                        switch(cell.index())
                        {
                            case 0:
                                csvFile << get<int>(cell);
                                break;
                            case 1:
                                csvFile << get<string>(cell);
                                break;
                            case 2:
                                csvFile << to_string(get<float>(cell));
                                break;
                            default:
                                throw runtime_error("Incorrect Type Included");
                                break;
                        }
                    }
                    catch(...){}
                    if(col != columns[columns.size() - 1]) csvFile << ",";
                }
                csvFile << '\n';
                
            }
            
            csvFile.close();
        }
        
        variant<int, string, float> sortType (string data)
        {
            data = trim(data);
            vector<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
            vector<char> chars = {};

            bool decimal = false;

            for(char c : data)
            {
                if (find(digits.begin(), digits.end(), c) == digits.end() && c != ' ')
                {
                    chars.push_back(c);
                }
            }

            if (chars.empty())
            {
                return stoi(data);
            }
            else if(chars[0] == '.')
            {
                return stof(data);
            }
            
            return trim(data);
        }

        string varToString (variant<int, string, float> data)
        {
            try
            {
                switch(data.index())
                {
                    case 0:
                        return to_string(get<int>(data));  
                        break;
                    case 2:
                        return get<string>(data);  
                        break;
                    case 3:
                        return to_string(get<float>(data));  
                        break;
                    
                }
            }
            catch(...){}

            return "Nothing here!";
        }

        void read()
        {
            map<string, vector<variant<int, string, float> > > result;

            ifstream csvFile(fileName.c_str());

            string error = "Could not open csv file ";

            error.append(fileName.c_str());
            
            try
            {
                if(!csvFile.is_open()) throw runtime_error(error);
            }
            catch(...)
            {
                cout << error << endl;
                return;
            }
            
            
            string line, columnName;
            string val;
            vector<string> columns;

            if(csvFile.good())
            {
                getline(csvFile, line);
                stringstream ss(line);

                while(getline(ss, columnName, ','))
                {
                    columnName = trim(columnName);
                    columns.push_back(columnName);
                    result[columnName] = vector<variant<int, string, float>>{};
                }
            }
            
            while(getline(csvFile, line))
            {
                stringstream ss(line);

                string temp = "";
                
                int col = 0;

                while(getline(ss, val, ','))
                {
                    int index = val.find('[');

                    if(index >= 0)
                    {
                        while(val.find(']') == -1)
                        {
                            temp += val + ',';
                            getline(ss, val, ',');
                        }
                        
                        temp += val;

                        val = temp;

                        temp ="";
                    }
                    result[columns[col]].push_back(sortType(val));
                    col++;

                }
                
                getline(ss, val, '\n');
            }

            csvFile.close();

            output = result;
        }

        void displayResult()
        {
            read();

            int j = 0;
            vector<string> columns; 

            for(const auto &[key, values] : output)
            {
                string columnName = key;
                
                cout << columnName;

                columns.push_back(columnName);

                if(j != output.size() - 1) cout << ", ";

                j++;
            }
            
            cout << '\n';

            for(int row = 0; row != output[columns[0]].size(); row++)
            {
                for(string col : columns)
                {
                    variant<int, string, float> cell = output[col][row];

                    try
                    {
                        
                        switch(cell.index())
                        {
                            
                            case 0:
                                cout << get<int>(cell);
                                break;
                            case 1:
                                cout << get<string>(cell);
                                break;
                            case 2:
                                cout << get<float>(cell);
                                break;
                            default:
                                throw runtime_error("Incorrect Type Included");
                                break;
                        }
                    }
                    catch(...)
                    {
                        cout << "Incorrect data type provided." << endl;
                        return;
                    }

                    if(col != columns[columns.size() - 1]) cout << ", ";
                }
                cout << '\n';
            }
            cout << '\n';
        }

        map<string, vector<variant<int, string, float> > > getResult()
        {
            read();
            return output;
        }

        void towxGrid(wxGrid *grid, string type="")
        {
            this->read();

            if(output.size() == 0)
            {
                cout << "Nothing in output";
                return;
            }
            // Create a wxGrid object
            grid->SetRowLabelSize(0);

            int rows = output.begin()->second.size();

            if(type == "student")
            {
                grid->CreateGrid(rows, output.size()+2);
            }
            else if(type == "course")
            {
                grid->CreateGrid(rows, output.size()+1);
            }
            else
            {
                grid->CreateGrid(rows, output.size());
            }

            map<string, vector<variant<int, string, float> > >::iterator it = output.begin();

            int col = 0;

            for(const auto& [key, value] : output)
            {
                col = distance(output.begin(), output.find(key));
                
                string colName = key;

                colName.erase(0,2);
                grid->SetColLabelValue(col, colName);
                int row = 0;
                for(variant<int, string, float> var : value)
                {
                    string cell = varToString(output[key][row]);
                    grid->SetCellValue(row, col, cell);
                    row++;
                }
            }

            col++;

            if(type == "student" || type == "course")
            {
                if (type == "student")
                {
                    grid->SetColLabelValue(col, "view marks");
                    grid->SetColLabelValue(col+1, "generate transcript");
                }
                else if (type == "course")
                {
                    grid->SetColLabelValue(col, "view assessments");
                }
                cout << "rows in student = " << rows << endl;
                for(int row = 0; row < rows; row++)
                {
                    cout << "putting out row " << row << endl;
                    grid->SetCellHighlightPenWidth(2);
                    grid->SetCellValue(row, col, wxT("view"));
                    grid->SetCellBackgroundColour(row, col, *wxGREEN);
                    grid->SetCellTextColour(row, col, *wxWHITE);
                    grid->SetCellAlignment(row, col, wxALIGN_CENTRE, wxALIGN_CENTRE);

                    if(type == "student")
                    {
                        grid->SetCellValue(row, col+1, wxT("generate"));
                        grid->SetCellBackgroundColour(row, col+1, *wxBLUE);
                        grid->SetCellTextColour(row, col+1, *wxWHITE);
                        grid->SetCellAlignment(row, col+1, wxALIGN_CENTRE, wxALIGN_CENTRE);
                    }
                    
                }
            }

            grid->AutoSize();
        }
};