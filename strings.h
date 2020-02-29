#include<string>

const std::string helpMsg="\nArguments are \n--daemon or -d to run as daemon\n--help for this menu\n --btle for manual source switch to btle\n --line1 for manual source switch to line1\n";

const std::string noArgs="\nRunning as current user...\n";

const std::string logo= R"(
                                         &&             #&.                                        
                                        &&&&             #&&&&                                      
                                     &&&&&&&      &/     #&&&&&&                                    
                                   &&&&&&&&&   ,&&&&&&   %&&&&&&&&&                                 
                                  &&&&&&&&&  &&&&&&&&&&&.  &&&&&&&&#                                
                              %&&&  &&&&   &&&&&&(,*&&&&&&&  %&&&  #&&&                             
                            &&&&&&&&/   &&&&&,   &&&&   &&&&&    &&&&&&&&/                          
                             &&&&&&&&&&&&&&&     &&&%    &&&&&&&&&&&&&&&(                           
                               /&&&&&&&&&&&&  &&&& &&&&& #&&&&&&&&&&&&                              
                              &&  &&&&&&&&#    &&   %&&    &&&&&&&&/ ,&(                            
                            &&&&&&  *&&&                     %&&&  &&&&&&&                          
                              &&&&&&&  *&&&               ,&&&  ,&&&&&&                             
                                ,&&&&&&&&                    &&&&&&&&                               
                                   &&&                         %&&)";

//https://raspberrypi.stackexchange.com/questions/68126/have-the-gpio-pins-changed-between-the-pi-2-and-the-pi-3
