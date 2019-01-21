#include<iostream>
#include<string>
#include<fstream>
#include<unistd.h> //STDERR_FILENO = 2, which exit the program and use write function to print out the error message.
#include<cstring>
#include<vector>
#include <bits/stdc++.h>
#include<algorithm>


using std::cout;
using std::endl;
std::vector<std::string> selection{
    "cd",
    "exit",
    "pwd"
};
static const int LOOP = 1; // without any errors, continue to execute the program.
static const int EXIT = 0; // when user type exit command in the program then exit safely.

void printStderr(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

void parseCommandLine(std::vector<std::string> &arguments, std::string line){
    std::stringstream inputString(line);
    std::string intermediate;
    while(getline(inputString,intermediate,' ')){
        if(intermediate == "")
            continue;
        
        arguments.push_back(intermediate);
    }
}

void excutePwdFunction(){
    char pwd[512];
    getcwd(pwd,sizeof(pwd));
    cout << pwd << endl;
}

void excuteCdFunction(std::vector<std::string> &arguments){
    unsigned int numOfElement = arguments.size();
    char* homeDir = getenv("HOME");
    char* currentDir;
    if(numOfElement == 1){
        if (chdir(homeDir) != 0)
            printStderr();
    }
    else if(numOfElement == 2){
        char pwd[512];
        getcwd(pwd,sizeof(pwd));
        strcat(pwd,"/");
        const char* newString = arguments[1].c_str();
        strcat(pwd,newString);
        if (chdir(pwd) != 0)
            printStderr();
    }
    else{
        printStderr();
    }
        
}


int excuteFunction(std::vector<std::string> &arguments){
    std::string command = arguments[0]; 
    if(command == "exit"){
        if(arguments.size() == 1){
            exit(0);
            return EXIT;
        }
        printStderr();
        
    }
    else if(command == "pwd"){
        if(arguments.size() == 1)
            excutePwdFunction();
        else{
            printStderr();
            return LOOP;
        }
            
    }
    else if(command == "cd"){
        excuteCdFunction(arguments);
    }
    return LOOP;
    
}



int main(int argc, char** argv){
    
    int status = 1;
    std::vector<std::string> arguments;//store the argument.
    std::string line;
    
    if(argc > 2){
        printStderr();
        exit(0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    }
    if(argc == 1){
   
    do{
        cout<<"mysh> ";
        std::getline(std::cin, line);
        
        //if input is more than 512 characters, then we need to rerun the process.
        if(line.length()>512)
            {
                printStderr();
                continue;
            }
        
        //read the input then store the arguments into the vector.
        parseCommandLine(arguments,line);
        
        //if we have empty command line
        if(arguments.size() == 0)
            continue;
        // store the command from the first element from the vector.
        std::string command = arguments[0]; 
        //if we can't find the command in the selection vector list, then we continue processing.
        if(std::find(selection.begin(),selection.end(),command) != selection.end())
            status = excuteFunction(arguments);
        else{
            status = 1; //if we can't find the command, then we continue the process.
            printStderr();
        }
            
        
        arguments.clear();
    }while(status);
    }
    
    else if(argc == 2){
        std::string fileName = argv[1];
        std::ifstream inputFile(fileName);
        if(inputFile.fail()){
            printStderr();
            exit(0);
        }
        while(std::getline(inputFile,line)){
            
        cout << line << endl;
        //if input is more than 512 characters, then we need to rerun the process.
        if(line.length()>512)
            {
                printStderr();
                continue;
            }
        
        //read the input then store the arguments into the vector.
        parseCommandLine(arguments,line);
        
        //if we have empty command line
        if(arguments.size() == 0)
            continue;
        // store the command from the first element from the vector.
        std::string command = arguments[0]; 
        //if we can't find the command in the selection vector list, then we continue processing.
        if(std::find(selection.begin(),selection.end(),command) != selection.end())
            status = excuteFunction(arguments);
        else{
            status = 1; //if we can't find the command, then we continue the process.
            printStderr();
        }
            
        
        arguments.clear();
        }
    }   
}
