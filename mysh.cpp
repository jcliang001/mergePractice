#include<iostream>
#include<string>
#include<fstream>
#include<unistd.h> //STDERR_FILENO = 2, which exit the program and use write function to print out the error message.
#include<cstring>
#include<vector>
#include <bits/stdc++.h>
#include<algorithm>
#include <sys/types.h> 
#include <sys/wait.h> 


using std::cout;
using std::endl;

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

void newProcess(std::vector<std::string> arguments){
    pid_t pid = -1;
    pid = fork();
    //after we initialize the pid, 
    if(pid == 0){
        int size = arguments.size();
        char *argm[size+1];
        for(unsigned int i=0; i < size; i++){
            std::strcpy (argm[i], arguments.at(i).c_str());
        }
        argm[size] = 0;
        execvp(argm[0],argm);
        //if the execvp fail to run, then it will execute the following statement.
        printStderr();
        exit(EXIT_FAILURE);
    }
    //after we finish the child process, then we need to wait the parent process to finish
    else if(pid > 0){
        wait(0);
        
    }
   // if the creation of a child process was unsuccessful, then the pid will return negative number
   else{
       printStderr();
       exit(EXIT_FAILURE);
   }
}



int main(int argc, char** argv){
    
    int status = 1;
    std::vector<std::string> arguments;//store the argument.
    std::string line;
    
    std::vector<std::string> selection{"cd","exit","pwd"};
    
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
            newProcess(arguments);
        }
            
        
        arguments.clear();
    }while(status);
    }
    
    else if(argc == 2){
        std::string fileName = argv[1];
        std::ifstream inputFile(fileName);
        if(inputFile.fail()){
            printStderr();
            exit(1);
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
            newProcess(arguments);
        }
            
        
        arguments.clear();
        }
    }   
}
