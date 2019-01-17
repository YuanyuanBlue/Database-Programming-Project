#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <vector>
#include "exerciser.h"
using namespace std;
using namespace pqxx;

void createTable(connection *C) {
  string db;
  string player;
  string team;
  string state;
  string color;

  color =  "CREATE TABLE COLOR (" \
           "COLOR_ID serial NOT NULL, " \
           "NAME text NOT NULL," \
           "PRIMARY KEY(COLOR_ID)" \
           ");";

  state = "CREATE TABLE STATE (" \
          "STATE_ID serial NOT NULL, " \
          "NAME text NOT NULL," \
          "PRIMARY KEY(STATE_ID)" \
          ");";

  team =  "CREATE TABLE TEAM (" \
          "TEAM_ID serial NOT NULL, " \
          "NAME text NOT NULL, " \
          "STATE_ID integer NOT NULL, " \
          "COLOR_ID integer NOT NULL, " \
          "WINS integer NOT NULL, " \
          "LOSSES integer NOT NULL," \
          "PRIMARY KEY(TEAM_ID)" \
          ");";

  player = "CREATE TABLE PLAYER (" \
           "PLAYER_ID serial NOT NULL, " \
           "TEAM_ID integer NOT NULL," \
           "UNIFORM_NUM integer NOT NULL," \
           "FIRST_NAME text NOT NULL," \
           "LAST_NAME text NOT NULL," \
           "MPG integer NOT NULL," \
           "PPG integer NOT NULL," \
           "RPG integer NOT NULL," \
           "APG integer NOT NULL," \
           "SPG double precision NOT NULL," \
           "BPG double precision NOT NULL," \
           "PRIMARY KEY(PLAYER_ID)" \
           ");";

  //      load each table with rows from the provided source txt files


      work A(*C);
      A.exec( color );
      A.exec( state );
      A.exec( team );
      A.exec( player );
      A.commit();
}

void parse(string s, vector<string> & v) {
  std::string delimiter = " ";
  size_t pos = 0;
  size_t p = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      if ((p = token.find("'")) != std::string::npos) {
        token.insert(p,"'");
      }
      v.push_back(token);
      s.erase(0, pos + delimiter.length());
  }
  v.push_back(s.substr(0, pos));
}

void addPlayer(string row, connection *C) {
  vector<string> v;
  parse(row, v);
  string sql;
  sql = "INSERT INTO PLAYER VALUES" \
  "("  + v[0] + "," + v[1] + "," + v[2] + "," + "'" + v[3] + "'," + "'" + v[4] + "'," + v[5] + "," + v[6]+ ","  + v[7] + "," + v[8]+ "," + v[9] + "," + v[10] + ");";
  work W(*C);
  W.exec( sql );
  W.commit();
}

void addTeam(string row, connection *C) {
  vector<string> v;
  parse(row, v);
  string sql;
  sql = "INSERT INTO TEAM VALUES" \
  "(" + v[0] + "," + "'" + v[1] + "', " + v[2] + "," + v[3] + "," + v[4] + "," + v[5] +  ");";
  work W(*C);
  W.exec( sql );
  W.commit();
}

void addState(string row, connection *C) {
  vector<string> v;
  parse(row, v);
  string sql;
  sql = "INSERT INTO STATE VALUES" \
  "(" + v[0] + ", " + "'" + v[1] + "'" +");";
  work W(*C);
  W.exec( sql );
  W.commit();
}

void addColor(string row, connection *C) {
  vector<string> v;
  parse(row, v);
  string sql;
  sql = "INSERT INTO COLOR VALUES" \
  "("  + v[0] + ", " + "'" + v[1] + "');";
  work W(*C);
  W.exec( sql );
  W.commit();
}

void addRow(connection *C) {
      string pline;
      ifstream playerf ("player.txt");
      if (playerf.is_open()) {
        while ( getline (playerf,pline) )
        {
          addPlayer(pline, C);
        }
        playerf.close();
      }

      string tline;
      ifstream teamf ("team.txt");
      if (teamf.is_open()) {
        while ( getline (teamf,tline) )
        {
          addTeam(tline, C);
        }
        teamf.close();
      }

      string sline;
      ifstream statef ("state.txt");
      if (statef.is_open()) {
        while ( getline (statef,sline) )
        {
          addState(sline, C);
        }
        statef.close();
      }

      string cline;
      ifstream colorf ("color.txt");
      if (colorf.is_open()) {
        while ( getline (colorf,cline) )
        {
          addColor(cline, C);
        }
        colorf.close();
      }
      
}

void dropTable(connection *C) {
      string sql1 = "DROP TABLE IF EXISTS PLAYER;";
      string sql2 = "DROP TABLE IF EXISTS TEAM;";
      string sql3 = "DROP TABLE IF EXISTS STATE;";
      string sql4 = "DROP TABLE IF EXISTS COLOR;";
      work W(*C);
//string sql5 = "DROP TABLE COLOR;";

    
//W.exec( sql5 );
      W.exec( sql1 );
      W.exec( sql2 );
      W.exec( sql3 );
      W.exec( sql4 );
      W.commit();
}

int main (int argc, char *argv[]) 
{


  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }

      dropTable(C);
      createTable(C);
      addRow(C);      

  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  exercise(C);


  //Close database connection
  C->disconnect();
  delete C;
  return 0;
}

