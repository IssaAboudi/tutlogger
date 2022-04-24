
#include "Application.hpp"

#define PADDING ImGui::NewLine()
#define SEPARATOR ImGui::Separator()
#define TIME_POINT std::chrono::system_clock::time_point

using namespace ImGui;
//======================================================
/*
 * Purpose of this program is to make logging tutoring hours
 * more convenient. When I tutor someone, I need to log the hours
 * I spend tutoring in a spreadsheet. Instead of always dealing
 * with the spreadsheet. This application would let me save it to a
 * text file which I can copy over to the spreadsheet after all my
 * sessions
 * ~ Matthew Issa Aboudi
 */
//======================================================

namespace tutlogger {
    static int f_numTutees = 0; //keeps track of number of tutees modified (to update to the file)

    void processFiles(std::vector<Student> &tutees){
        //Create folder for our program to store data in (easily accessible by the user)

        std::string folder = getFilePath(); //stores OS specific file path (see function definition)

        if(!createFolder(folder)){ //verify that folders were generated/loaded correctly
            //Otherwise, give an error message
            std::cout << "Error code -999: Could not create Directory. Press enter to close" << std::endl;
            std::cin.get();
            exit(-999);
        }

        std::fstream tutoringFile; //to reference the text file


        loadRecords(folder, tutees); //read in Student data from JSON file
        makeLog(folder, tutoringFile); //opens the log file for editing - if it doesn't exists, creates it.

        tutoringFile.close(); //close file when loaded data.
    }



    void createWindow(std::vector<Student> &tutees, Student** active){ //handles the onscreen windows - within while loop

            static bool opt_fullscreen = true;
            static bool opt_padding = false;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
            // because it would be confusing to have two docking targets within each others.
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen)
            {
                const ImGuiViewport* viewport = GetMainViewport();
                SetNextWindowPos(viewport->WorkPos);
                SetNextWindowSize(viewport->WorkSize);
                SetNextWindowViewport(viewport->ID);
                PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }
            else
            {
                dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
            }

            // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
            // and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
            // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
            // all active windows docked into it will lose their parent and become undocked.
            // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
            // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
            if (!opt_padding)
                PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            Begin("DockSpace", nullptr, window_flags);
            if (!opt_padding)
                PopStyleVar();

            if (opt_fullscreen)
                PopStyleVar(2);

            // Submit the DockSpace
            ImGuiIO& io = GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = GetID("MyDockSpace");
                DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

    //        if (BeginMenuBar()) {
    //
    //            if (BeginMenu("Options")) {
    //                // Disabling fullscreen would allow the window to be moved to the front of other windows,
    //                // which we can't undo at the moment without finer window depth/z control.
    //                MenuItem("Fullscreen", NULL, &opt_fullscreen);
    //                EndMenu();
    //            }
    //            EndMenuBar();
    //        }

        End();

        static TIME_POINT startTime;
        static TIME_POINT endTime;

        //redundancy to prevent button 1 from running button 2 code
        static bool b1_pressed = false; //is button 1 pressed
        static bool b2_pressed = false; //is button 2 pressed

        Begin("Main Application"); //Application Window

        Text("Tutor Logging Tool"); //Title
        Text("==================");

        //[Add Session] - First Button
        //============================

        //variables for first button:
        static int checked = 0; //Which index of tutees we are currently working on
        static int tempMin; //save entered time in GUI window

        if(Button("1) Add new session")){
            b1_pressed = true;
            OpenPopup("newSession");
        }
        if (BeginPopup("newSession", ImGuiWindowFlags_NoTitleBar)) {
            Text("Select tutee:");
            SEPARATOR;
            for (int i = 0; i < tutees.size(); ++i) { //displays all of the tutees
                if(Button(tutees[i].name.c_str(), ImVec2(140, 30))) {
                    checked = i; //save selected tutee's index (so we can refer to it in bool array)
                    tutees[i].selected = true; //keep track of which tutee was selected
                }
            }
            EndPopup();
        }
        if(tutees[checked].selected && b1_pressed){
            Text("Enter Hours Logged (min) for");

            SameLine(); Text("%s",tutees[checked].name.c_str());
            SameLine(); Text(": ");


            InputInt("##Hours", &tempMin, 10); //go up 10 minutes at a time

            //EXIT
            if(Button("Exit", ImVec2(240, 40)) || IsKeyPressed(526)){ //526 is escape
                tutees[checked].selected = false; //reset - collapse the entry field
                tempMin = 0; //reset value to 0 (so everyone starts at 0);
                b1_pressed = false; //we are done with this button
            }
            //DONE
            else if(SameLine(); Button("Done", ImVec2(240, 40)) || IsKeyPressed(525)){ //525 is the enter key
                LOG("CreateWindow: Before add " << tutees[checked].tempTime);
                tutees[checked].tempTime += abs(tempMin); //add hours entered to student member TODO: push it back to the JSON and Text
                LOG("CreateWindow: " << tutees[checked].tempTime << " hour added: " << abs(tempMin));
                LOG("CreateWindow: After add " << tutees[checked].tempTime);

                active[f_numTutees] = &tutees[checked]; //reference tutees updated to put in the file
                f_numTutees++; //move forwards an index to next empty space.
                LOG("CreateWindow: closed menu");
                tutees[checked].selected = false; //reset - collapses the entry field
                tempMin = 0; //reset value to 0 (so everyone starts at 0);
                b1_pressed = false; //we are done with this button
            }
        }

        //[Time Session] - Second Button
        //==============================


        if(Button("2) Time session")){
            //after timing session we need to select tutee to apply time recorded to
            b2_pressed = true;
            OpenPopup("Pick Tutee");

        }
        //selects tutee to time for
        if(BeginPopupModal("Pick Tutee", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            Text("Select tutee:");
            SEPARATOR;
            for (int i = 0; i < tutees.size(); ++i) { //displays all of the tutees
                if(Button(tutees[i].name.c_str(), ImVec2(140, 30))) {
                    checked = i; //store the index of the tutee selected (matches with index in parallel bool array)
                    tutees[i].selected = true; //mark true for tutee at that index in parallel bool array

                } else if(IsKeyPressed(526)){
                    CloseCurrentPopup();
                } else {}
            }
            EndPopup();
        }

        if(tutees[checked].selected && b2_pressed){
            tutees[checked].selected = false; //collapse window
            LOG("CreateWindow: Open Popup");
            OpenPopup("Time Session"); //open time session window
        }


        SetNextWindowPos(GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if(BeginPopupModal("Time Session", NULL, ImGuiWindowFlags_AlwaysAutoResize)){

            static bool pressStart = false; //Begin timer when start button pressedColor
            static bool pressStop = false; //Stop timer when stop button pressedColor
            static bool isPressed = false; // Check if timer already started

            Text("Press the startTime button when you startTime your session. \n\t\t\tWhen you're done, press the stop button\n\n");
            SEPARATOR;
            PADDING;

            //Start & Stop Buttons + Coloring

            static const ImVec4 startColor START_COLOR; //set startTime button color
            static const ImVec4 stopColor STOP_COLOR; //set stop button color
            static const ImVec4 pressedColor PRESSED_COLOR; //set pressedColor color
            static ImVec4 start_current = startColor;

            //=====================================================================================
            //Start Button
            SameLine(100);
            BeginGroup();
            PushStyleColor(ImGuiCol_Button, start_current);
            if(Button("Start", ImVec2(150, 60)) && !isPressed){
                pressStart = true; //start timer
                isPressed = true; //set it, so we can't restart the timer by pressing the button
                start_current = pressedColor; //grey out button
            }
            PopStyleColor();


            //Stop Button
            SameLine(200);
            PushStyleColor(ImGuiCol_Button, stopColor);
            if(Button("Stop", ImVec2(150, 60))){
                pressStop = true;
            }
            PopStyleColor();
            EndGroup();
            //=====================================================================================

            if(pressStart){
                LOG("CreateWindow: Start Button Pressed");
                startTime = std::chrono::system_clock::now(); //record start time
                endTime = std::chrono::system_clock::now(); //this just so it doesn't display garbage before we click stop button
                pressStart = false; //unclick the button
            }
            if(pressStop){
                LOG("CreateWindow: Stop Button Pressed");
                endTime = std::chrono::system_clock::now(); //record end time
                pressStop = false; //unclick the button
                isPressed = false; //unblock start button - let us be able to click start again
                start_current = startColor; //reset startTime button color back
            }

            float minutes = 0.0;
            std::chrono::duration<float> duration = endTime - startTime; //calculate duration
#if LOGGING == ON
            minutes = std::chrono::duration_cast<std::chrono::seconds>(duration).count(); //for debugging purposes, we're gonna treat seconds as minutes
#elif LOGGING == OFF
            minutes = std::chrono::duration_cast<std::chrono::seconds>(duration).count() / 60;
#endif
            Text("%s",std::to_string(minutes).c_str());



            PADDING;
            //EXIT BUTTON
            SameLine(350);
            if( Button("Exit", ImVec2(120, 40)) || IsKeyPressed(526)) { //526 is escape
                CloseCurrentPopup();
                b2_pressed = false;
            }
            //SAVE BUTTON
            SameLine(500);
            if (Button("Save", ImVec2(120, 40))|| IsKeyPressed(525)) { //525 is enter
                tutees[checked].tempTime += minutes;
                active[f_numTutees] = &tutees[checked]; //reference tutees updated to put in the file
                f_numTutees++; //move forwards an index
                CloseCurrentPopup();
                LOG("CreateWindow: Minutes at Close " << minutes );
                startTime = std::chrono::system_clock::now();
                endTime = std::chrono::system_clock::now();
                b2_pressed = false;
            } //exit
            EndPopup();
        }

        //[Add Tutee] - Third Button
        //==========================

        if(Button("3) Add new Tutee")){
            OpenPopup("Add Tutee");
        }
        if(BeginPopupModal("Add Tutee", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
            static char name[64] = "";
            static char subject[64] = "";


            Text("Enter tutee Name and Subject");
            SEPARATOR;
            PADDING;

            //Label and Text Input for adding new tutee
            Text("Name:"); InputText("##", name, 64);
            PADDING;
            Text("Subject:"); InputText("###", subject, 64);

            //Vertical Padding between text input and buttons
            PADDING; PADDING;

            SameLine(15);
            //Exit popup without adding new tutee / Discard Changes
            if (Button("Exit", ImVec2(120, 40)) || IsKeyPressed(526)) {
                CloseCurrentPopup();
            }

            //Add new tutee and close popup / Apply Changes
            SameLine(220);
            if (Button("Apply", ImVec2(120, 40)) || IsKeyPressed(525)) {
                Student tempStudent; //make new student
                tempStudent.name = name; //copy name
                tempStudent.subject = subject; //copy subject

                tutees.push_back(tempStudent);//add it to the vector of all students
                CloseCurrentPopup();
            } //Apply

            EndPopup();
        }

        //[List Tutees] - Fourth Button
        //=============================

        //variables for fourth button:
        static int listButton = 0;

        if(Button("4) List all Tutees")){
            listButton++;
        }
        if(listButton & 1){
            for (int i = 0; i < tutees.size(); ++i) { //displays all of the current tutees
                Text("%s",tutees[i].name.c_str());
            }
        }

        //[Update Log] - Fifth Button
        //=============================

        if(Button("5) Update Log")){
            updateFile(active, tutees);
        }

        End();
    }

    Status updateFile(Student** active, std::vector<Student>&tutees){
        static bool cleared = false;
        //if there are no students currently being worked on - should not update file
        if(active[0] == nullptr && !cleared){ //if first student reference is not filled with data, then nope out
            return EMPTY; //there's nothing to write to the files
            LOG("updateFile: Update a student or add a new student before writing to a file");
        }

        if(f_numTutees < 1){
            LOG("updateFile: ERROR: No tutees modified yet");
            return EMPTY;
        } else {

            static std::string txt = getFilePath();
            static std::string json = txt;
            txt += "/tutoringLog.txt"; //text file
            json += "/students.json"; // json file
            std::fstream tutoringFile(txt, std::fstream::app); //open the txt file to update first:

            int hour;
            int min;

            //Writes out to the text file
            for (int i = 0; i < f_numTutees; i++) {
                hour = active[i]->tempTime / 60; // extract hours
                min = active[i]->tempTime % 60;  // extract minutes
                tutoringFile << active[i]->name << " | " << getDate() << " : " << active[i]->subject
                             << " - " << hour << " hour(s) and " << min << " minutes" << std::endl;

                active[i]->time += active[i]->tempTime; //add time to total time
                active[i]->tempTime = 0; //reset tempTime to 0
            }
            LOG("updateFile: Updated text file");
            tutoringFile.close(); //close previous file
            tutoringFile.open(json, std::ios::out); //open the json file

            //Write out to the json file
            nlohmann::json studentArray = nlohmann::json::array(); //json array to store data to file
            for (int i = 0; i < tutees.size(); i++) {
                nlohmann::json data;
                nlohmann::json header;

                //Store data in JSON format
                data["Subject"] = tutees[i].subject;
                data["#ofSessions"] = tutees[i].numSessions;
                data["Total Time"] = tutees[i].time;

                //Put data under header:
                header[tutees[i].name] = data; //creates header for data organized.
                studentArray.push_back(header); //All data under "header" now, push into total array

            }
            tutoringFile << std::setw(4) << studentArray;
            LOG("updateFile: Updated JSON file");
            tutoringFile.close(); // done with the file

            // Once we write out everything to the files, we can reset the temporary array:
            for (int i = 0; i < f_numTutees; i++) {
                active[i] = nullptr;
                cleared = true;
            }
            LOG("updateFile: Successfully added Record");
            return FILLED;
        }

    }

    // This is just for reference - not actually used
    void tutorialWindow() {

        //Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // 1. Show the big demo window (Most of the sample code is in ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            Text("This is some useful text.");               // Display some text (you can use a format strings too)
            Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            Checkbox("Another Window", &show_another_window);

            SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            SameLine();
            Text("counter = %d", counter);

            Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / GetIO().Framerate, GetIO().Framerate);
            End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            Text("Hello from another window!");
            if (Button("Close Me"))
                show_another_window = false;
            End();
        }
    }
} //end of namespace


void unitTest(){
    //Testing here
    std::string folder = getFilePath();
    if(createFolder(folder) == true){
        LOG("True");
    } else {
        LOG("False");
    }
}

void clearCIN(void){
    //Clears Cin Buffer - ignores rest of input
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

std::string getDate(void){ //get only date in a string
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t printTime = std::chrono::system_clock::to_time_t(today);
    std::string dateTime = ctime(&printTime); //convert time to a string

    std::string date = dateTime.substr(0,10); //store only date
    std::string year = dateTime.substr(20,4); //get the year
    date += " ";
    date += year;
    return date;
}

std::string getDateTime(void){ //get both date and time in one string
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t printTime = std::chrono::system_clock::to_time_t(today);
    std::string dateTime = ctime(&printTime); //convert time to a string
    return dateTime;
}

std::string getTime(void){ //get only time in a string
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t printTime = std::chrono::system_clock::to_time_t(today);
    std::string dateTime = ctime(&printTime); //convert time to a string
    std::string time = dateTime.substr(11);
    return time;
}

std::pair<std::string, std::string> breakTime(std::string inString, char delim){
    //This function is about splitting a string into smaller strings using a specified delimiter.
    //For this program, I want the time to be split in two.
    //Left of the delimeter would be Hours and Right would be minutes


    std::vector<std::string> collection; //holds the broken up strings
    std::string part;

    std::pair<std::string, std::string> finalPair; //will be returned at the end

    //holds location of things in the string (start, end, delim etc)
    unsigned long startPos = 0; //references first character of the string
    unsigned long delimPos = 0; //references first delimiter
    unsigned long endPos = inString.size(); //references last character of string

    //initialize the positions
    if(inString.find(delim) == std::string::npos) { //if not found in string
        delimPos = inString.size(); //store pos last character in string
    } else {
        delimPos = inString.find(delim); //store pos where delim found in string
    }

    //Loop goes through the bigger string and breaks down each part of the string according to the delimiter
    do {
        if (startPos == endPos) { //if reached the end of the string
            break; //break out of the loop
        }
        part = inString.substr(startPos, delimPos - startPos); //stores part (leading up to the delim) in string
        if (delimPos + 1 < endPos){
            delimPos++; //moving one character past the delim in the string
        }
        startPos = delimPos; //stores next part after delim (leading up to next delim)
        if(inString.find(delim, delimPos) == std::string::npos) { //if not found in string
            delimPos = inString.size(); //store pos last character in string
        } else {
            delimPos = inString.find(delim, delimPos); //store pos where delim found in string
        }

        collection.push_back(part); //add part to the vector
    } while(delimPos != std::string::npos);

    //in this particular instance, we are only expecting two items to be added to the vector (hour and minute)
    finalPair = std::make_pair(collection[0], collection[1]);

    return finalPair;
}



//DEPRICATED: (TODO:Remove)
void addNewSession(std::fstream &file, Student* student){
    std::string input = "";
    std::string numInput = "";
    while(input == "") {
        std::cout << "Please enter what subject you tutored in: "; //this could be unneccessary if everything is contained to Student objects
        std::getline(std::cin, input);
    }
    while(numInput == "") {
        std::cout << "How many minutes was your session?: ";
        std::getline(std::cin, numInput);
    }

    //edit student attributes;
    student->time += std::stoi(numInput);
    student->numSessions++;

    std::cout << "Time is: " << student->time << std::endl;
    int hour = std::stoi(numInput) / 60;
    int min = std::stoi(numInput) % 60;

    //TODO: Migrate writing out to file to its own function
    // - We'll need a pointer array to point to the modified tutees to do this in:
    file << student->name << " | " << getDate() << " : " << input << " - " << hour << " hour(s) and " << min << " minutes";
    file << std::endl;
}

void addNewSession(std::fstream &file, float &time, Student* student){
    std::string input;
    std::cout << "Please enter what subject you tutored in: ";
    std::getline(std::cin, input);

    student->time += time;
    student->numSessions++;

    int hour = (int)time / 60;
    int min = (int)time % 60;

    //TODO: Migrate writing out to file to its own function
    // - We'll need a pointer array to point to the modified tutees to do this in:
    file << student->name << " | " << getDate() << " : " << input << " - " << hour << " hour(s) and " << min << " minutes";
    file << std::endl;
}

void timeSession(std::fstream &file, Student* student){
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;

    start = std::chrono::system_clock::now(); //records begin time

    std::cout << "Press any key when you reach the end of your session" << std::endl;
    while (!std::cin.get()) { /*Just waits for end of session*/ }

    end = std::chrono::system_clock::now(); //records end time

    std::chrono::duration<float> duration = end - start; //calculate duration
    float minutes = std::chrono::duration_cast<std::chrono::seconds>(duration).count() / 60;
    LOG("timeSession: " << minutes);

    addNewSession(file, minutes, student); //adds to log file
}

void addTutee(const std::string &filePath, std::vector<Student> &students) {
    std::string input;
    Student temp;

    SPACER();

    std::cout << "Add Tutee: " << std::endl;
    std::cout << "-=-=-=-=-=-" << std::endl;
    std::cout << "Enter Tutee name: ";
    std::getline(std::cin, input);
    temp.name = input;


    std::cout << "Enter Tutee Subject: "; //TODO: Make this more robust - what about multiple subjects?
    std::getline(std::cin, input);
    temp.subject = input; //Possibly irrelevant?

    students.push_back(temp);
    updateRecords(filePath, students);

    SPACER();
}

void listStudents(std::vector<Student> &students){
    if(students.size() < 1){
        return;
    }
    SPACER();
    std::cout << "Your Tutees" << std::endl;
    std::cout << "-=-=-=-=-=-" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        std::cout << i << " : " << students[i] << std::endl;
    }
    SPACER();
}

Student* selectTutee(std::vector<Student> &students){
    int menuInput;
    Student* student;

    listStudents(students);
    std::cout << "Please select a tutee for the session: " << std::endl;
    std::cout << ">> ";
    std::cin >> menuInput;
    clearCIN();

    SPACER();

    student = &students[menuInput];
    return student;
}


//===============================
//This is the console application version of the tutorLogging - depreciated
//===============================

void consoleApp(){
    //Create folder for our program to store data in (easily accessible by the user)
    std::string folder = getFilePath(); //stores OS specific file path (see function definition)

    if(!createFolder(folder)){ //verify that folders were generated/loaded correctly
        //Otherwise, give an error message
        std::cout << "Error code -999: Could not create Directory. Press enter to close" << std::endl;
        std::cin.get();
        exit(-999);
    }

    std::fstream tutoringFile; //to reference the text file
    int menuInput; //userInput for the menu
    std::vector<Student> tutees; //vector of students
    Student* student = nullptr; //specific Student we want to reference
    bool firstRun = false;

    loadRecords(folder, tutees); //read in Student data from JSON file
    makeLog(folder, tutoringFile); //opens the log file for editing - if it doesn't exists, creates it.

    do {
        if(tutees.size() < 1){
            std::cout << "Need to add a Tutee before proceeding" << std::endl;
            addTutee(folder, tutees);
        } else if(firstRun == false){
            listStudents(tutees);
            firstRun = true;
        }

        //menu for tutlogger application & selection //TODO: make this a function
        std::cout << "Tutoring Logging Tool" << std::endl;
        std::cout << "-=-=-=-=-=-=-=-=-=-=-" << std::endl;
        LOG(getDateTime());
        std::cout << "1) Add new session" << std::endl;
        std::cout << "2) Time new session" << std::endl;
        std::cout << "3) Add new Tutee" << std::endl;
        std::cout << "4) List all Tutees" << std::endl;
        std::cout << "5) Exit" << std::endl;
        std::cout << ">> ";
        std::cin >> menuInput;
        clearCIN(); //clear cin buffer


        switch(menuInput){
            case 1:
                student = selectTutee(tutees); //returns pointer to specific tutee we are working with in vector
                addNewSession(tutoringFile, student); //manually enter session details
                updateRecords(folder, tutees); //apply changes to the JSON file
                break;
            case 2:
                student = selectTutee(tutees); //returns pointer to specific tutee we are working with in vector
                timeSession(tutoringFile, student); //begins a timer
                updateRecords(folder, tutees); //apply changes to the JSON file
                break;
            case 3:
                addTutee(folder, tutees);
                break;
            case 4:
                listStudents(tutees); //displays students in vector
                break;
        }
    } while(menuInput != 5);

    //TODO: Separate entries by day rather than program runs
    tutoringFile << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl; //divide different program runs


    tutoringFile.close();

    SPACER();
    LOG("Program Ending");
}

//int main() {
//#if UNIT_TEST == OFF
//    consoleApp();
//#else
//    unitTest();
//#endif
//    return 0;
//}

