#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME marqs


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  bool found_stronger_weapon(Pos cell_pos, Pos prev_cell_pos, WeaponType warrior_weapon, vector<vector<int>> &distance, int current_distance, queue<Pos> &q, vector<vector<Pos>> &previous)
  {
    //if the weapon is worse or the same it will count as a building since it is not accesible without picking it up. also with cells occuped by other citizens or occuiped by barricades
    if (not pos_ok(cell_pos))
    {
      //cerr << "FUERA DEL TABLERO" << endl;
      return false;
    }
    if (cell(cell_pos).type == Building) 
    {
      //cerr << "EDIFICIO" << endl;
      return false;
    }
    if (distance[cell_pos.i][cell_pos.j] != -1)
    {
      //cerr << "VISITADO" << endl;
      return false;
    } 
    if (cell(cell_pos).weapon == warrior_weapon)
    {
      //cerr << "MISMA ARMA" << endl;
      return false;
    }
    if (cell(cell_pos).weapon != NoWeapon and strongestWeapon(cell(cell_pos).weapon, warrior_weapon) == warrior_weapon)
    {
      //cerr << "PEOR ARMA" << endl;
      return false;
    }
    if (cell(cell_pos).id != -1)
    {
      //cerr << "POS OCUPADA POR CITIZEN" << endl;
      return false;
    }
    if (cell(cell_pos).b_owner != -1)
    {
        //cerr << "HAY BARRICADA" << endl;
        return false;
    }
    else if (strongestWeapon(cell(cell_pos).weapon, warrior_weapon) != warrior_weapon) 
    {
      previous[cell_pos.i][cell_pos.j] = prev_cell_pos;
      //cerr << "ARMA ENCONTRADA" << endl;
      return true;
    }
    else
    {
      //cerr << "SIGAMOS" << endl;
      distance[cell_pos.i][cell_pos.j] = current_distance;
      previous[cell_pos.i][cell_pos.j] = prev_cell_pos;
      q.push(cell_pos);
      return false;
    }
  }
  // returns the position of the nearest item_type to the citizien in citizen_pos and the path to get there
  Pos weapon_bfs(Pos warrior_pos, WeaponType warrior_weapon, vector<Pos>& weapon_path)
  {
    vector<vector<int>> distance(board_rows(), vector<int>(board_cols(), -1)); //stores the distance from the warrior to each cell
    vector<vector<Pos>> previous(board_rows(), vector<Pos>(board_cols(), Pos(-1,-1))); //stores the previous cell in the path to each cell
    queue<Pos> q;
    distance[warrior_pos.i][warrior_pos.j] = 0;
    q.push(warrior_pos);
    Pos found_pos = Pos(-1, -1);
    while (not q.empty())
    {
      Pos current_pos = q.front();
      q.pop();
      int current_distance = distance[current_pos.i][current_pos.j] + 1;
      if (found_stronger_weapon(Pos(current_pos.i + 1, current_pos.j), current_pos, warrior_weapon, distance, current_distance, q, previous)) //DOWN
      {
        found_pos = Pos(current_pos.i + 1, current_pos.j);
        break;
      }
      else if (found_stronger_weapon(Pos(current_pos.i - 1, current_pos.j), current_pos, warrior_weapon, distance, current_distance, q, previous)) //UP
      {
        found_pos = Pos(current_pos.i - 1, current_pos.j);
        break;
      }
      else if (found_stronger_weapon(Pos(current_pos.i, current_pos.j + 1), current_pos, warrior_weapon, distance, current_distance, q, previous)) //RIGHT
      {
        found_pos = Pos(current_pos.i, current_pos.j + 1);
        break;
      }
      else if (found_stronger_weapon(Pos(current_pos.i, current_pos.j - 1), current_pos, warrior_weapon, distance, current_distance, q, previous)) //LEFT
      {
        found_pos = Pos(current_pos.i, current_pos.j - 1);
        break;
      }
    }
    if (found_pos.i != -1 and found_pos.j != -1)
    {
      Pos current_pos = found_pos;
      while (current_pos != warrior_pos)
      {
        weapon_path.push_back(current_pos);
        current_pos = previous[current_pos.i][current_pos.j];
      }
    }
    return found_pos;
  }
    
  bool found_item(Pos cell_pos, Pos prev_cell_pos, vector<vector<int>> &distance, int current_distance, queue<Pos> &q, vector<vector<Pos>> &previous, BonusType item)
  {
    if (not pos_ok(cell_pos))
    {
      //cerr << "FUERA DEL TABLERO" << endl;
      return false;
    }
    if (cell(cell_pos).type == Building) 
    {
      //cerr << "EDIFICIO" << endl;
      return false;
    }
    if (distance[cell_pos.i][cell_pos.j] != -1)
    {
      //cerr << "VISITADO" << endl;
      return false;
    }
    if (cell(cell_pos).id != -1)
    {
      //cerr << "POS OCUPADA POR CITIZEN" << endl;
      return false;
    }
    if (cell(cell_pos).b_owner != -1)
    {
        //cerr << "HAY BARRICADA" << endl;
        return false;
    }
    else if (cell(cell_pos).bonus == item) 
    {
      previous[cell_pos.i][cell_pos.j] = prev_cell_pos;
      //cerr << "COMIDA ENCONTRADA" << endl;
      return true;
    }
    else
    {
      //cerr << "SIGAMOS" << endl;
      distance[cell_pos.i][cell_pos.j] = current_distance;
      previous[cell_pos.i][cell_pos.j] = prev_cell_pos;
      q.push(cell_pos);
      return false;
    }
  }

  Pos item_bfs(Pos citizen_pos, vector<Pos> &item_path, BonusType item)
  {
    vector<vector<int>> distance(board_rows(), vector<int>(board_cols(), -1)); //stores the distance from the warrior to each cell
    vector<vector<Pos>> previous(board_rows(), vector<Pos>(board_cols(), Pos(-1,-1))); //stores the previous cell in the path to each cell
    queue<Pos> q;
    distance[citizen_pos.i][citizen_pos.j] = 0;
    q.push(citizen_pos);
    Pos found_pos = Pos(-1, -1);
    while (not q.empty())
    {
      Pos current_pos = q.front();
      q.pop();
      int current_distance = distance[current_pos.i][current_pos.j] + 1;
      if (found_item(Pos(current_pos.i + 1, current_pos.j), current_pos, distance, current_distance, q, previous, item)) //DOWN
      {
        found_pos = Pos(current_pos.i + 1, current_pos.j);
        break;
      }
      else if (found_item(Pos(current_pos.i - 1, current_pos.j), current_pos, distance, current_distance, q, previous, item)) //UP
      {
        found_pos = Pos(current_pos.i - 1, current_pos.j);
        break;
      }
      else if (found_item(Pos(current_pos.i, current_pos.j + 1), current_pos, distance, current_distance, q, previous, item)) //RIGHT
      {
        found_pos = Pos(current_pos.i, current_pos.j + 1);
        break;
      }
      else if (found_item(Pos(current_pos.i, current_pos.j - 1), current_pos, distance, current_distance, q, previous, item)) //LEFT
      {
        found_pos = Pos(current_pos.i, current_pos.j - 1);
        break;
      }
    }
    if (found_pos.i != -1 and found_pos.j != -1)
    {
      Pos current_pos = found_pos;
      while (current_pos != citizen_pos)
      {
        item_path.push_back(current_pos);
        current_pos = previous[current_pos.i][current_pos.j];
      }
    }
    return found_pos;
  }

  bool found_enemy(Pos cell_pos, Pos prev_cell_pos, vector<vector<int>> &distance, int current_distance, queue<Pos> &q, vector<vector<Pos>> &previous, CitizenType enemy)
  {
    if (not pos_ok(cell_pos))
    {
      //cerr << "FUERA DEL TABLERO" << endl;
      return false;
    }
    if (cell(cell_pos).type == Building) 
    {
      //cerr << "EDIFICIO" << endl;
      return false;
    }
    if (distance[cell_pos.i][cell_pos.j] != -1)
    {
      //cerr << "VISITADO" << endl;
      return false;
    }
    if (cell(cell_pos).id != -1 and citizen(cell(cell_pos).id).player == me())
    {
      //cerr << "POS OCUPADA POR CITIZEN" << endl;
      return false;
    }
    if (cell(cell_pos).b_owner != -1 and cell(cell_pos).b_owner != me())
    {
      //cerr << "HAY BARRICADA" << endl;
      return false;
    }
    else if (cell(cell_pos).id != -1 and citizen(cell(cell_pos).id).type == enemy)
    {
      previous[cell_pos.i][cell_pos.j] = prev_cell_pos;
      //cerr << "ENEMIGO ENCONTRADO" << endl;
      return true;
    }
    else
    {
      //cerr << "SIGAMOS" << endl;
      distance[cell_pos.i][cell_pos.j] = current_distance;
      previous[cell_pos.i][cell_pos.j] = prev_cell_pos;
      q.push(cell_pos);
      return false;
    }
  }

  Pos enemy_bfs(Pos citizen_pos, vector<Pos> &enemy_path, CitizenType enemy)
  {
    vector<vector<int>> distance(board_rows(), vector<int>(board_cols(), -1)); //stores the distance from the warrior to each cell
    vector<vector<Pos>> previous(board_rows(), vector<Pos>(board_cols(), Pos(-1,-1))); //stores the previous cell in the path to each cell
    queue<Pos> q;
    distance[citizen_pos.i][citizen_pos.j] = 0;
    q.push(citizen_pos);
    Pos found_pos = Pos(-1, -1);
    while (not q.empty())
    {
      Pos current_pos = q.front();
      q.pop();
      int current_distance = distance[current_pos.i][current_pos.j] + 1;
      if (found_enemy(Pos(current_pos.i + 1, current_pos.j), current_pos, distance, current_distance, q, previous, enemy)) //DOWN
      {
        found_pos = Pos(current_pos.i + 1, current_pos.j);
        break;
      }
      else if (found_enemy(Pos(current_pos.i - 1, current_pos.j), current_pos, distance, current_distance, q, previous, enemy)) //UP
      {
        found_pos = Pos(current_pos.i - 1, current_pos.j);
        break;
      }
      else if (found_enemy(Pos(current_pos.i, current_pos.j + 1), current_pos, distance, current_distance, q, previous, enemy)) //RIGHT
      {
        found_pos = Pos(current_pos.i, current_pos.j + 1);
        break;
      }
      else if (found_enemy(Pos(current_pos.i, current_pos.j - 1), current_pos, distance, current_distance, q, previous, enemy)) //LEFT
      {
        found_pos = Pos(current_pos.i, current_pos.j - 1);
        break;
      }
    }
    if (found_pos.i != -1 and found_pos.j != -1)
    {
      Pos current_pos = found_pos;
      while (current_pos != citizen_pos)
      {
        enemy_path.push_back(current_pos);
        current_pos = previous[current_pos.i][current_pos.j];
      }
    }
    return found_pos;
  }

  bool buildable(Pos cell_pos)
  {
    if (not pos_ok(cell_pos))
    {
      //cerr << "FUERA DEL TABLERO" << endl;
      return false;
    }
    if (cell(cell_pos).type == Building)
    {
      //cerr << "EDIFICIO" << endl;
      return false;
    }
    if (cell(cell_pos).id != -1)
    {
      //cerr << "POS OCUPADA POR CITIZEN" << endl;
      return false;
    }
    if (cell(cell_pos).b_owner != -1 and cell(cell_pos).b_owner != me())
    {
      //cerr << "NO ES TU BARRICADA" << endl;
      return false;
    }
    return true;
  }

  Pos barricade_available(Pos citizen_pos)
  {
    if (cell(Pos(citizen_pos.i + 1, citizen_pos.j)).b_owner == me() and cell(Pos(citizen_pos.i + 1, citizen_pos.j)).id == -1) return Pos(citizen_pos.i + 1, citizen_pos.j); //DOWN
    if (cell(Pos(citizen_pos.i - 1, citizen_pos.j)).b_owner == me() and cell(Pos(citizen_pos.i - 1, citizen_pos.j)).id == -1) return Pos(citizen_pos.i - 1, citizen_pos.j); //UP
    if (cell(Pos(citizen_pos.i, citizen_pos.j + 1)).b_owner == me() and cell(Pos(citizen_pos.i, citizen_pos.j + 1)).id == -1) return Pos(citizen_pos.i, citizen_pos.j + 1); //RIGHT
    if (cell(Pos(citizen_pos.i, citizen_pos.j - 1)).b_owner == me() and cell(Pos(citizen_pos.i, citizen_pos.j - 1)).id == -1) return Pos(citizen_pos.i, citizen_pos.j - 1); //LEFT
    return Pos(-1, -1);
  }
  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    vector<int> my_builders = builders(me());
    vector<int> my_warriors = warriors(me());
    if (is_day())
    {
      /////////////////////////////////////////////////////////
      ////////////////////////DAY TIME////////////////////////
      ///////////////////////////////////////////////////////

      ///////////////////////WARRIORS//////////////////////////
      for (int i = 0; i < int(my_warriors.size()); ++i) 
      {
        ////////!!!!!!!!!!!!!!!!!!!!! QUIZAS VALE LA PENA PRIORIZAR OTRA COSA QUE NO CURARSE CON LA ESTRATEGIA???
        Pos my_warrior_pos = citizen(my_warriors[i]).pos;
        if (citizen(my_warriors[i]).life != citizen_ini_life(Warrior))
        ////////////////////////////////////
        //SEEK FOR THE NEAREST HEALING ITEM
        ///////////////////////////////////
        {
          vector<Pos> healing_path;
          Pos nearest_healing = item_bfs(my_warrior_pos, healing_path, Food);
          if (nearest_healing.i != -1 and nearest_healing.j != -1)
          {
            Dir direction;
            int n = healing_path.size() - 1;
            if (healing_path[n].i > my_warrior_pos.i) direction = Down;
            else if (healing_path[n].i < my_warrior_pos.i) direction = Up;
            else if (healing_path[n].j < my_warrior_pos.j) direction = Left;
            else direction = Right;
            move(my_warriors[i], direction);
          }
        }
        else if (citizen(my_warriors[i]).weapon != Bazooka)
        ////////////////////////////////////////////////////////////////////////////
        //SEEK FOR THE NEAREST BETTER WEAPON THAN THE ACTUAL IF NOT BAZOOKA EQUIPED
        ///////////////////////////////////////////////////////////////////////////
        {
          vector<Pos> weapon_path; 
          Pos nearest_weapon = weapon_bfs(my_warrior_pos, citizen(my_warriors[i]).weapon, weapon_path);
          if (nearest_weapon.i != -1 and nearest_weapon.j != -1)
          {
            Dir direction;
            int n = weapon_path.size() - 1;
            if (weapon_path[n].i > my_warrior_pos.i) direction = Down;
            else if (weapon_path[n].i < my_warrior_pos.i) direction = Up;
            else if (weapon_path[n].j < my_warrior_pos.j) direction = Left;
            else direction = Right;
            move(my_warriors[i], direction);
          }
        }
        else
        ////////////////////////////////////
        //SEEK FOR THE NEAREST BAG OF MONEY
        ///////////////////////////////////
        {
          vector<Pos> money_path;
          Pos nearest_money = item_bfs(my_warrior_pos, money_path, Money);
          if (nearest_money.i != -1 and nearest_money.j != -1)
          {
            Dir direction;
            int n = money_path.size() - 1;
            if (money_path[n].i > my_warrior_pos.i) direction = Down;
            else if (money_path[n].i < my_warrior_pos.i) direction = Up;
            else if (money_path[n].j < my_warrior_pos.j) direction = Left;
            else direction = Right;
            move(my_warriors[i], direction);
          }
        }
      }
      ////////////////////BUILDERS/////////////////////
      for (int i = 0; i < int(my_builders.size()); ++i)
      {
        Pos my_builder_pos = citizen(my_builders[i]).pos;
        int game_round = round();
        if (((game_round >= 17 and game_round <= 24) or (game_round >= 67 and game_round <= 74) or (game_round >= 117 and game_round <= 124) or (game_round >= 167 and game_round <= 174)
          or (game_round >= 217 and game_round <= 224)) and ((int(barricades(me()).size()) < 3) or barricade_available(my_builder_pos).i != -1))
          ///////////////////////////////////////////////////////////////////////
          /////////////////////BUILD BARRICADE BEFORE NIGHT/////////////////////
          /////////////////////////////////////////////////////////////////////
          {
            //cerr << "BUILDING BARRICADE " << my_builder_pos << endl;
            if (buildable(Pos(my_builder_pos.i + 1, my_builder_pos.j))) //DOWN
            {
              //cerr << "BUILDING DOWN" << endl;
              build(my_builders[i], Down);
            }
            else if (buildable(Pos(my_builder_pos.i - 1, my_builder_pos.j))) //UP
            {
              //cerr << "BUILDING UP" << endl;
              build(my_builders[i], Up);
            }
            else if (buildable(Pos(my_builder_pos.i, my_builder_pos.j + 1))) //RIGHT
            {
              //cerr << "BUILDING RIGHT" << endl;
              build(my_builders[i], Right);
            }
            else if (buildable(Pos(my_builder_pos.i, my_builder_pos.j - 1))) //LEFT
            {
              //cerr << "BUILDING LEFT" << endl;
              build(my_builders[i], Left);
            }
          }
          else if (citizen(my_builders[i]).life != citizen_ini_life(Builder))
          {
            ////////////////////////////////////
            //SEEK FOR THE NEAREST HEALING ITEM
            ///////////////////////////////////
            vector<Pos> healing_path;
            Pos nearest_healing = item_bfs(my_builder_pos, healing_path, Food);
            if (nearest_healing.i != -1 and nearest_healing.j != -1)
            {
              Dir direction;
              int n = healing_path.size() - 1;
              if (healing_path[n].i > my_builder_pos.i) direction = Down;
              else if (healing_path[n].i < my_builder_pos.i) direction = Up;
              else if (healing_path[n].j < my_builder_pos.j) direction = Left;
              else direction = Right;
              move(my_builders[i], direction);
            }
          }
          else
          {
            /////////////////////////////////////////////////////
            //////////////SEEK FOR THE NEAREST MONEY BAG////////
            ///////////////////////////////////////////////////
            vector<Pos> money_path;
            Pos nearest_money = item_bfs(my_builder_pos, money_path, Money);
            if (nearest_money.i != -1 and nearest_money.j != -1)
            {
              Dir direction;
              int n = money_path.size() - 1;
              if (money_path[n].i > my_builder_pos.i) direction = Down;
              else if (money_path[n].i < my_builder_pos.i) direction = Up;
              else if (money_path[n].j < my_builder_pos.j) direction = Left;
              else direction = Right;
              move(my_builders[i], direction);
            }
          }
      }
    }
    else
    {
      ///////////////////////////////////////////////////////////
      ////////////////////////NIGHT TIME////////////////////////
      /////////////////////////////////////////////////////////
    
      /////////////////////////////////WARRIORS////////////////////////////////
      for (int i = 0; i < int(my_warriors.size()); ++i)
      {
        Pos my_warrior_pos = citizen(my_warriors[i]).pos;
        if (citizen(my_warriors[i]).life >= 40)
        ///////////////////////////////////////
        ///////SEEK FOR THE CLOSEST CONSTRUCTOR OR WARRIOR IF NOT CONSTRUCTOR HAS BEEN FOUND///////
        {
          vector<Pos> enemy_path;
          Pos nearest_enemy = enemy_bfs(my_warrior_pos, enemy_path, Builder);
          if (nearest_enemy.i != -1 and nearest_enemy.j != -1)
          {
            //cerr << "ENEMY FOUND " << my_warrior_pos << endl;
            Dir direction;
            int n = enemy_path.size() - 1;
            if (enemy_path[n].i > my_warrior_pos.i) direction = Down;
            else if (enemy_path[n].i < my_warrior_pos.i) direction = Up;
            else if (enemy_path[n].j < my_warrior_pos.j) direction = Left;
            else direction = Right;
            //cerr << direction << endl;
            move(my_warriors[i], direction);
          }
        }
        else if (citizen(my_warriors[i]).life != citizen_ini_life(Warrior))
        //////////////////////////SEEK FOR THE CLOSEST HEALING////////////////////////
        {
          vector<Pos> healing_path;
          Pos nearest_healing = item_bfs(my_warrior_pos, healing_path, Food);
          if (nearest_healing.i != -1 and nearest_healing.j != -1)
          {
            Dir direction;
            int n = healing_path.size() - 1;
            if (healing_path[n].i > my_warrior_pos.i) direction = Down;
            else if (healing_path[n].i < my_warrior_pos.i) direction = Up;
            else if (healing_path[n].j < my_warrior_pos.j) direction = Left;
            else direction = Right;
            move(my_warriors[i], direction);
          }
        }
        else
        {
          //////////////////////////////SEEK FOR THE CLOSES MONEY BAG////////////////////////
          vector<Pos> money_path;
          Pos nearest_money = item_bfs(my_warrior_pos, money_path, Money);
          if (nearest_money.i != -1 and nearest_money.j != -1)
          {
            Dir direction;
            int n = money_path.size() - 1;
            if (money_path[n].i > my_warrior_pos.i) direction = Down;
            else if (money_path[n].i < my_warrior_pos.i) direction = Up;
            else if (money_path[n].j < my_warrior_pos.j) direction = Left;
            else direction = Right;
            move(my_warriors[i], direction);
          }
        }
      }
      for (int i = 0; i < int(my_builders.size()); ++i)
      {
        Pos my_builders_pos = citizen(my_builders[i]).pos;
        if (citizen(my_builders[i]).life != citizen_ini_life(Builder))
        {
          vector<Pos> healing_path;
          Pos nearest_healing = item_bfs(my_builders_pos, healing_path, Food);
          if (nearest_healing.i != -1 and nearest_healing.j != -1)
          {
            Dir direction;
            int n = healing_path.size() - 1;
            if (healing_path[n].i > my_builders_pos.i) direction = Down;
            else if (healing_path[n].i < my_builders_pos.i) direction = Up;
            else if (healing_path[n].j < my_builders_pos.j) direction = Left;
            else direction = Right;
            move(my_builders[i], direction);
          }
        }
        else if (cell(my_builders_pos).b_owner != me()) //it's not inside a barricade
        {
          Pos nearest_barricade = barricade_available(my_builders_pos);
          if (nearest_barricade.i != -1 and nearest_barricade.j != -1)
          {
            ///////////////////////MOVE INTO BARRICADE/////////////////////
            Dir direction;
            if (nearest_barricade.i > my_builders_pos.i) direction = Down;
            else if (nearest_barricade.i < my_builders_pos.i) direction = Up;
            else if (nearest_barricade.j < my_builders_pos.j) direction = Left;
            else direction = Right;
            move(my_builders[i], direction);
          }
          else
          {
            ////////////////////SEEK FOR THE CLOSEST MONEY BAG//////////////////////
            vector<Pos> money_path;
            Pos nearest_money = item_bfs(my_builders_pos, money_path, Money);
            if (nearest_money.i != -1 and nearest_money.j != -1)
            {
              Dir direction;
              int n = money_path.size() - 1;
              if (money_path[n].i > my_builders_pos.i) direction = Down;
              else if (money_path[n].i < my_builders_pos.i) direction = Up;
              else if (money_path[n].j < my_builders_pos.j) direction = Left;
              else direction = Right;
              move(my_builders[i], direction);
            }
          }
        }
    }
  }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
