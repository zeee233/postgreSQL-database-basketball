#include "query_funcs.h"

void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
    try
    {
        work w(*C);
        string res = "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) VALUES (" + w.quote(team_id) + ", " + w.quote(jersey_num) + ", " + w.quote(first_name) + ", " + w.quote(last_name) + ", " + w.quote(mpg) + ", " + w.quote(ppg) + ", " + w.quote(rpg) + ", " + w.quote(apg) + ", " + w.quote(spg) + ", " + w.quote(bpg) + ");";
        w.exec(res);
        w.commit();
    }
    catch (const std::exception &e)
    {
        cerr << "there is error with add_player: \n" << e.what() << std::endl;
    }
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
    try
    {
    work w(*C);
    stringstream res;
    res << "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) VALUES ("
        << w.quote(name) + ", " + w.quote(state_id) + ", " + w.quote(color_id) + ", " + w.quote(wins) + ", " + w.quote(losses) + ");";
    w.exec(res.str());
    w.commit();
    }
  catch (const std::exception &e) {
    cerr << "there is error with add_team: \n" << e.what() << std::endl;
  }  
}


void add_state(connection *C, string name)
{
    try
    {
        work w(*C);
        string res = "INSERT INTO STATE (NAME) VALUES (" + w.quote(name) + ");";
        w.exec(res);
        w.commit();
    }
    catch (const std::exception &e)
    {
        cerr << "there is error with add_state: \n" << e.what() << std::endl;
    }
}


void add_color(connection *C, string name)
{
    try
    {
        work w(*C);
        string res = "INSERT INTO COLOR (NAME) VALUES (" + w.quote(name) + ");";
        w.exec(res);
        w.commit();
    }
    catch (const std::exception &e)
    {
        cerr << "there is error with add_color: \n" << e.what() << std::endl;
    }
}

/*
 * All use_ params are used as flags for corresponding attributes
 * a 1 for a use_ param means this attribute is enabled (i.e. a WHERE clause is needed)
 * a 0 for a use_ param means this attribute is disabled
 */
void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
  string sql = "SELECT * FROM PLAYER";
  //no_condition means that there is no where clause now
  bool no_condition = true;
  work w(*C);
  if (use_mpg) {
    sql += " WHERE MPG BETWEEN " + to_string(min_mpg) + " AND " + to_string(max_mpg);
    no_condition = false;
  }
  if (use_ppg) {
      if (no_condition) {
          sql += " WHERE";
          no_condition = false;
      }
      else {
          sql += " AND";
      }
      sql += " PPG BETWEEN " + to_string(min_ppg) + " AND " + to_string(max_ppg);
  }
  if (use_rpg) {
      if (no_condition) {
          sql += " WHERE";
          no_condition = false;
      }
      else {
          sql += " AND";
      }
      sql += " RPG BETWEEN " + to_string(min_rpg) + " AND " + to_string(max_rpg);
  }  
  if (use_apg) {
      if (no_condition) {
          sql += " WHERE";
          no_condition = false;
      }
      else {
          sql += " AND";
      }
      sql += " APG BETWEEN " + to_string(min_apg) + " AND " + to_string(max_apg);
  }
  if (use_spg) {
      if (no_condition) {
          sql += " WHERE";
          no_condition = false;
      }
      else {
          sql += " AND";
      }
      sql += " SPG BETWEEN " + to_string(min_spg) + " AND " + to_string(max_spg);
  }
  if (use_bpg) {
      if (no_condition) {
          sql += " WHERE";
          no_condition = false;
      }
      else {
          sql += " AND";
      }
      sql += " BPG BETWEEN " + to_string(min_bpg) + " AND " + to_string(max_bpg);
  }
  sql += ";";
  
  result r = w.exec(sql);
  printResult(r);
}


void query2(connection *C, string team_color)
{
    work w(*C);
    string sql = "SELECT t.NAME FROM TEAM t JOIN COLOR c ON t.COLOR_ID = c.COLOR_ID WHERE c.NAME = " + w.quote(team_color) +";";
    //sql = "SELECT * FROM TEAM WHERE COLOR_ID = (SELECT COLOR_ID FROM COLOR WHERE NAME = " + w.quote(team_color) +");";
    result r = w.exec(sql);
    printResult(r);
}


void query3(connection *C, string team_name)
{
  work w(*C);
  string sql = "SELECT p.first_name, p.last_name FROM PLAYER p JOIN TEAM t ON p.team_id = t.team_id WHERE t.name = "+ w.quote(team_name) + " ORDER BY p.ppg DESC;";
  result r = w.exec(sql);
  printResult(r);
  
}


void query4(connection *C, string team_state, string team_color)
{
  work w(*C);
  string sql = "SELECT UNIFORM_NUM, FIRST_NAME, LAST_NAME "
                "FROM PLAYER p "
                "JOIN TEAM t ON p.TEAM_ID = t.TEAM_ID "
                "JOIN STATE s ON t.STATE_ID = s.STATE_ID "
                "JOIN COLOR c ON t.COLOR_ID = c.COLOR_ID "
                "WHERE s.NAME = " + w.quote(team_state) + 
                " AND c.NAME = " + w.quote(team_color) + ";";
  result r = w.exec(sql);
  printResult(r);
}


void query5(connection *C, int num_wins)
{
  work w(*C);
  string sql = "SELECT p.FIRST_NAME, p.LAST_NAME, t.NAME, t.WINS \
              FROM PLAYER p\
              JOIN TEAM t ON p.TEAM_ID = t.TEAM_ID \
              WHERE t.WINS > " + to_string(num_wins) + ";";
  result r = w.exec(sql);
  printResult(r);
}
void printResult(const result& r) {
    // Get the number of rows and columns in the result set
    const int num_cols = r.columns();
    const int num_rows = r.size();

    // Print the column names
    for (int i = 0; i < num_cols; i++) {
        string column_name = r.column_name(i);
        for (char& c : column_name) {
            c = toupper(c);
        }
        cout << column_name << " ";
    }
    cout << endl;

    // Print the data
    for (int i = 0; i < num_rows; i++) {
      //row is the type result::tuple
        const auto row = r[i];
        for (int j = 0; j < num_cols; j++) {
          //when access the result::tuple , it returned result::field, contert to any type use 'as' 
            cout << row[j].as<string>() << " ";
        }
        cout << endl;
    }
    //writeResult(r);
}

void writeResult(const result& r) {
    ofstream output("result.txt", ios::trunc); // add ios::trunc flag to overwrite the old file

    const int num_cols = r.columns();
    const int num_rows = r.size();

    // Capitalize column names and write to file
    for (int i = 0; i < num_cols; i++) {
        std::string column_name = r.column_name(i);
        for (char& c : column_name) {
            c = toupper(c);
        }
        output << column_name << " ";
    }
    output << endl;

    // Write the data
    for (int i = 0; i < num_rows; i++) {
        const auto row = r[i];
        for (int j = 0; j < num_cols; j++) {
            output << row[j].as<string>() << " ";
        }
        output << endl;
    }
    output.close();
}

void createTables(connection *C){
    work w(*C);
    w.exec("DROP TABLE IF EXISTS PLAYER;");
    w.exec("DROP TABLE IF EXISTS TEAM;");
    w.exec("DROP TABLE IF EXISTS STATE;");
    w.exec("DROP TABLE IF EXISTS COLOR;");
    //w.commit();
    string createStateTable = "CREATE TABLE STATE(" \
        "STATE_ID SERIAL PRIMARY KEY NOT NULL," \
        "NAME VARCHAR(50) NOT NULL);";
    string createColorTable = "CREATE TABLE COLOR(" \
        "COLOR_ID SERIAL PRIMARY KEY NOT NULL," \
        "NAME VARCHAR(50) NOT NULL);";    
    // one team can have many players,while one player can
    // only have one team
    string createTeamTable = "CREATE TABLE TEAM(" \
        "TEAM_ID SERIAL NOT NULL," \
        "NAME VARCHAR(50) NOT NULL," \
        "STATE_ID INT NOT NULL," \
        "COLOR_ID INT NOT NULL," \
        "WINS INT NOT NULL," \
        "LOSSES INT NOT NULL,"\
        "PRIMARY KEY (TEAM_ID),"\
        "FOREIGN KEY (STATE_ID) REFERENCES STATE(STATE_ID) ON DELETE CASCADE ON UPDATE CASCADE,"\
        "FOREIGN KEY (COLOR_ID) REFERENCES COLOR(COLOR_ID) ON DELETE CASCADE ON UPDATE CASCADE);";
    string createPlayerTable = "CREATE TABLE PLAYER(" \
        "PLAYER_ID SERIAL NOT NULL," \
        "TEAM_ID INT NOT NULL," \
        "UNIFORM_NUM INT NOT NULL," \
        "FIRST_NAME VARCHAR(50) NOT NULL," \
        "LAST_NAME VARCHAR(50) NOT NULL," \
        "MPG INT NOT NULL," \
        "PPG INT NOT NULL," \
        "RPG INT NOT NULL," \
        "APG INT NOT NULL," \
        "SPG DECIMAL(4,1) NOT NULL," \
        "BPG DECIMAL(4,1) NOT NULL,"\
        "PRIMARY KEY (PLAYER_ID),"\
        "FOREIGN KEY (TEAM_ID) REFERENCES TEAM(TEAM_ID) ON DELETE CASCADE ON UPDATE CASCADE);";
    w.exec(createStateTable);
    w.exec(createColorTable);
    w.exec(createTeamTable);
    w.exec(createPlayerTable);
    w.commit();
}

void loadStateTable(connection *C) {
    ifstream infile("state.txt");
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int stateId;
        string name;
        if (!(iss >> stateId >> name)) { 
          cerr << "Error: Unable to parse line - " << line << endl; 
          continue;
        } // error
        add_state(C,  name);
    }
}

void loadColorTable(connection *C) {
    ifstream infile("color.txt");
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int colorId;
        string name;
        if (!(iss >> colorId >> name)) { 
          cerr << "Error: Unable to parse line - " << line << endl; 
          continue;
        } // error
        add_color(C, name);
    }
}

void loadTeamTable(connection *C) {
    ifstream infile("team.txt");
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int teamId, stateId, colorId, wins, losses;
        string name;
        if (!(iss >> teamId >> name >> stateId >> colorId >> wins >> losses)) { 
          cerr << "Error: Unable to parse line - " << line << endl; 
          continue;
        } // error
        add_team(C, name, stateId, colorId, wins, losses);
    }
}

void loadPlayerTable(connection *C) {
    ifstream infile("player.txt");
    string line;
    while (getline(infile, line)) {
      //cout<<line<<endl;
        istringstream iss(line);
        int playerId, teamId, uniformNum;
        string firstName, lastName;
        double mpg, ppg, rpg, apg, spg, bpg;
        //work w(*C);
        if (!(iss >> playerId >> teamId >> uniformNum >> firstName >> lastName >> mpg >> ppg >> rpg >> apg >> spg >> bpg)) { 
          cerr << "Error: Unable to parse line - " << line << endl; 
          continue;
        } // error
        add_player(C, teamId, uniformNum, firstName, lastName,  mpg, ppg, rpg, apg, spg, bpg);
    }
}

void loadTableInorder(connection *C){
  loadStateTable(C);
  loadColorTable(C);
  loadTeamTable(C);
  loadPlayerTable(C);
}