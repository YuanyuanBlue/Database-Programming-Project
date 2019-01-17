#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{	
	string seq;
  	seq = "SELECT setval('player_player_id_seq', max(PLAYER_ID)) FROM PLAYER;";

	stringstream nteam_id;
	stringstream njersey_num;
	stringstream nmpg;
	stringstream nppg;
	stringstream nrpg;
	stringstream napg;
	stringstream nspg;
	stringstream nbpg;
	nteam_id << team_id;
	nmpg << mpg;
	nppg << ppg;
	nrpg << rpg;
	napg << apg;
	nspg << spg;
	nbpg << bpg;
	string sql;
	sql = "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) VALUES "  \
         "(" + string(nteam_id.str()) + "," + njersey_num.str() + "," + "'" + first_name + "'," + "'" + last_name + "'," + nmpg.str() + "," + nppg.str()+ ","  + nrpg.str() + "," + napg.str() + "," + nspg.str() + "," + nbpg.str() + ");";
    work W(*C);
    W.exec( seq );
    W.exec( sql );
    W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{	
	string seq;
  	seq = "SELECT setval('team_team_id_seq', max(TEAM_ID)) FROM TEAM;";

	stringstream nstate_id;
	stringstream ncolor_id;
	stringstream nwins;
	stringstream nlosses;
	nstate_id << state_id;
	ncolor_id << color_id;
	nwins << wins;
	nlosses << losses;
	string sql;
	sql = "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) VALUES "  \
         "("  + string(" '") + name + "', " + nstate_id.str() + "," + ncolor_id.str() + "," + nwins.str() + "," + nlosses.str() +  ");";
    work W(*C);
    W.exec( seq );
    W.exec( sql );
    W.commit();
}


void add_state(connection *C, string name)
{

  string seq;
  seq = "SELECT setval('state_state_id_seq', max(STATE_ID)) FROM STATE;";
  string sql;
  sql = "INSERT INTO STATE (NAME) VALUES " \
  "(" + string("'") + name + "'" +");";
  work W(*C);
  W.exec( seq );
  W.exec( sql );
  W.commit();

  /*SELECT setval('state_state_id_seq', max(STATE_ID)) FROM STATE;
	INSERT INTO STATE (NAME) VALUES ('SH');*/
}


void add_color(connection *C, string name)
{
  string seq;
  seq = "SELECT setval('color_color_id_seq', max(COLOR_ID)) FROM COLOR;";

  string sql;
  sql = "INSERT INTO COLOR (NAME) VALUES " \
  "(" + string("'") + name + "'" +");";
  work W(*C);
  W.exec( seq );
  W.exec( sql );
  W.commit();
}


void query1Print(result R) {
	cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << c[0].as<int>() << " ";
         cout << c[1].as<int>() << " ";
         cout << c[2].as<int>() << " ";
         cout << c[3].as<string>() << " ";
         cout << c[4].as<string>() << " ";
         cout << c[5].as<int>() << " ";
         cout << c[6].as<int>() << " ";
         cout << c[7].as<int>() << " ";
         cout << c[8].as<int>() << " ";
         cout << c[9].as<double>() << " ";
         cout << c[10].as<double>()<<endl;
      }
}

/*void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
	nontransaction N(*C);
	string sql;
	stringstream n1;
	stringstream n2;
	if(use_mpg) {
		n1 << min_mpg;
		n2 << max_mpg;
		sql = "SELECT * FROM PLAYER WHERE MPG >=" + std::string(n1.str()) + "AND MPG <=" + std::string(n2.str()) + ";";
		result R( N.exec( sql ));
		query1Print(R);
	}

	if(use_ppg) {
		n1 << min_ppg;
		n2 << max_ppg;
		sql = "SELECT * FROM PLAYER WHERE PPG >=" + std::string(n1.str()) + "AND PPG <=" + std::string(n2.str()) + ";";
		result R( N.exec( sql ));
		query1Print(R);
	}

	if(use_rpg) {
		n1 << min_rpg;
		n2 << max_rpg;
		sql = "SELECT * FROM PLAYER WHERE RPG >=" + std::string(n1.str()) + "AND RPG <=" + std::string(n2.str()) + ";";
		result R( N.exec( sql ));
		query1Print(R);
	}

	if(use_apg) {
		n1 << min_apg;
		n2 << max_apg;
		sql = "SELECT * FROM PLAYER WHERE APG >=" + std::string(n1.str()) + "AND APG <=" + std::string(n2.str()) + ";";
		result R( N.exec( sql ));
		query1Print(R);
	}

	if(use_spg) {
		n1 << min_spg;
		n2 << max_spg;
		sql = "SELECT * FROM PLAYER WHERE SPG >=" + std::string(n1.str()) + "AND SPG <=" + std::string(n2.str()) + ";";
		result R( N.exec( sql ));
		query1Print(R);
	}

	if(use_bpg) {
		n1 << min_bpg;
		n2 << max_bpg;
		sql = "SELECT * FROM PLAYER WHERE BPG >=" + std::string(n1.str()) + "AND BPG <=" + std::string(n2.str()) + ";";
		result R( N.exec( sql ));
		query1Print(R);
	}

}*/

void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
	nontransaction N(*C);
	int count = 0;
	string sql;
	string sql1;
	string sql2;
	string sql3;
	string sql4;
	string sql5;
	string sql6;
	stringstream n1;
	stringstream n2;
	if(use_mpg) {
		count++;
		n1 << min_mpg;
		n2 << max_mpg;
		sql1 = " MPG >= " + std::string(n1.str()) + " AND MPG <=" + std::string(n2.str());
		if(count == 1) {
			sql = "SELECT * FROM PLAYER WHERE " + sql1;
		} else {
			sql = sql + " AND " + sql1;
		}
		n1.str("");
		n2.str("");
	}

	if(use_ppg) {
		count++;
		n1 << min_ppg;
		n2 << max_ppg;
		sql2 = " PPG >= " + std::string(n1.str()) + " AND PPG <=" + std::string(n2.str());
		if(count == 1) {
			sql = "SELECT * FROM PLAYER WHERE " + sql2;
		} else {
			sql = sql + " AND " + sql2;
		}
		n1.str("");
                n2.str("");
	}

	if(use_rpg) {
		count++;
		n1 << min_rpg;
		n2 << max_rpg;
		sql3 = " RPG >= " + std::string(n1.str()) + " AND RPG <=" + std::string(n2.str());
		if(count == 1) {
			sql = "SELECT * FROM PLAYER WHERE " + sql3;
		} else {
			sql = sql + " AND " + sql3;
		}
                n1.str("");
                n2.str("");
	}

	if(use_apg) {
		count++;
		n1 << min_apg;
		n2 << max_apg;
		sql4 = " APG >= " + std::string(n1.str()) + " AND APG <=" + std::string(n2.str());
		if(count == 1) {
			sql = "SELECT * FROM PLAYER WHERE " + sql4;
		} else {
			sql = sql + " AND " + sql4;
		}
                n1.str("");
                n2.str("");
	}

	if(use_spg) {
		count++;
		n1 << min_spg;
		n2 << max_spg;
		sql5 = " SPG >= " + std::string(n1.str()) + " AND SPG <=" + std::string(n2.str());
		if(count == 1) {
			sql = "SELECT * FROM PLAYER WHERE " + sql5;
		} else {
			sql = sql + " AND " + sql5;
		}
                n1.str("");
                n2.str("");
	}

	if(use_bpg) {
		count++;
		n1 << min_bpg;
		n2 << max_bpg;
		sql6 = " BPG >= " + std::string(n1.str()) + " AND BPG <=" + std::string(n2.str());
		if(count == 1) {
			sql = "SELECT * FROM PLAYER WHERE " + sql6;
		} else {
			sql = sql + " AND " + sql6;
		}
                n1.str("");
                n2.str("");
	}

	sql = sql + ";";
//cout<<sql;
	result R( N.exec( sql ));
	query1Print(R);

}

void query2Print(result R) {
	cout << "NAME" << endl;
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << c[0].as<string>()<<endl;
      }
}

void query2(connection *C, string team_color)
{
	nontransaction N(*C);
	string sql;
	sql = "SELECT TEAM.NAME " \
		  "FROM TEAM "\
	      "INNER JOIN COLOR " \
		  "ON TEAM.COLOR_ID = COLOR.COLOR_ID " \
		  "WHERE COLOR.NAME = " + string("'") + team_color + "';";
	result R( N.exec( sql ));
	query2Print(R);
}


void query3Print(result R){
	cout << "FIRST_NAME ";
	cout << "LAST_NAME" << endl;
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << c[0].as<string>() << " ";
         cout << c[1].as<string>()<<endl;
      }
}

void query3(connection *C, string team_name)
{
	nontransaction N(*C);
	string sql;
	sql = "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME " \
		  "FROM PLAYER " \
		  "INNER JOIN TEAM " \
		  "ON PLAYER.TEAM_ID = TEAM.TEAM_ID " \
		  "WHERE TEAM.NAME = " + string("'") + team_name + "'" + " ORDER BY PLAYER.PPG DESC;";
	result R( N.exec( sql ));
	query3Print(R);  
}

void query4Print(result R) {
	cout << "FIRST_NAME ";
	cout << "LAST_NAME ";
	cout << "UNIFORM_NUM" << endl;
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << c[0].as<string>() << " ";
         cout << c[1].as<string>() << " ";
         cout << c[2].as<int>() << endl;
      }
}

void query4(connection *C, string team_state, string team_color)
{
	nontransaction N(*C);
	string sql;
	sql = "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, PLAYER.UNIFORM_NUM " \
		  "FROM PLAYER " \
		  "INNER JOIN TEAM " \
		  "ON PLAYER.TEAM_ID = TEAM.TEAM_ID " \
		  "INNER JOIN STATE " \
		  "ON TEAM.STATE_ID = STATE.STATE_ID " \
		  "INNER JOIN COLOR " \
		  "ON TEAM.COLOR_ID = COLOR.COLOR_ID " \
		  "WHERE STATE.NAME = " + string("'") + team_state + "' " +  "AND COLOR.NAME = " +  string("'") + team_color + "';";
		  result R( N.exec( sql ));
		  query4Print(R); 
}

void query5Print(result R) {
	cout << "FIRST_NAME ";
	cout << "LAST_NAME ";
	cout << "NAME ";
	cout << "WINS" << endl;
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << c[0].as<string>() << " ";
         cout << c[1].as<string>() << " ";
         cout << c[2].as<string>() << " ";
         cout << c[3].as<int>() << endl;
      }
}

void query5(connection *C, int num_wins)
{
	nontransaction N(*C);
	string sql;
	stringstream n;
	n << num_wins;

	sql = "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, TEAM.NAME, TEAM.WINS " \
		  "FROM PLAYER " \
		  "INNER JOIN TEAM " \
		  "ON PLAYER.TEAM_ID = TEAM.TEAM_ID " \
		  "WHERE TEAM.WINS > " + string(n.str()) + ";";
		  result R( N.exec( sql ));
		  query5Print(R);
}


