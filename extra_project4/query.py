from load import session
from sqlalchemy import desc
from model import STATE, COLOR, TEAM, PLAYER
def query1(session,
           use_mpg, min_mpg, max_mpg,
           use_ppg, min_ppg, max_ppg,
           use_rpg, min_rpg, max_rpg,
           use_apg, min_apg, max_apg,
           use_spg, min_spg, max_spg,
           use_bpg, min_bpg, max_bpg):

    # Build the query gradually based on the input parameters
    query = session.query(PLAYER)

    if use_mpg:
        query = query.filter(PLAYER.MPG.between(min_mpg, max_mpg))
    if use_ppg:
        query = query.filter(PLAYER.PPG.between(min_ppg, max_ppg))
    if use_rpg:
        query = query.filter(PLAYER.RPG.between(min_rpg, max_rpg))
    if use_apg:
        query = query.filter(PLAYER.APG.between(min_apg, max_apg))
    if use_spg:
        query = query.filter(PLAYER.SPG.between(min_spg, max_spg))
    if use_bpg:
        query = query.filter(PLAYER.BPG.between(min_bpg, max_bpg))
    """
    query = session.query(Player).filter(
        (not use_mpg) | (Player.MPG.between(min_mpg, max_mpg)),
        (not use_ppg) | (Player.PPG.between(min_ppg, max_ppg)),
        (not use_rpg) | (Player.RPG.between(min_rpg, max_rpg)),
        (not use_apg) | (Player.APG.between(min_apg, max_apg)),
        (not use_spg) | (Player.SPG.between(min_spg, max_spg)),
        (not use_bpg) | (Player.BPG.between(min_bpg, max_bpg))
    )
    """

    # Execute the query and return the results
    results = query.all()
    print("PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG")
    # 'f' allows us to embed expressions inside string literals, using {} characters
    # print(f"My name is {name} and I am {age} years old.")
    # print("My name is {} and I am {} years old.".format(name, age))
    for player in results:
        print(f"{player.PLAYER_ID} {player.TEAM_ID} {player.UNIFORM_NUM} {player.FIRST_NAME} {player.LAST_NAME} {player.MPG} {player.PPG} {player.RPG} {player.APG} {player.SPG:.1f} {player.BPG:.1f}")
    #return results
def query2(session, team_color):
    teams = session.query(TEAM).join(COLOR).filter(COLOR.NAME == team_color).all()
    print("NAME")
    for team in teams:
        print(team.NAME)
def query3(session, team_name):
    results = session.query(PLAYER).join(TEAM).filter(TEAM.NAME == team_name).order_by(desc(PLAYER.PPG)).all()
    print("FIRST_NAME LAST_NAME")
    for player in results:
        print(player.FIRST_NAME, player.LAST_NAME)
def query4(session, team_state, team_color):
    players = session.query(PLAYER).join(TEAM).join(STATE).join(COLOR).filter(
        STATE.NAME == team_state,
        COLOR.NAME == team_color
    ).all()

    print("UNIFORM_NUM FIRST_NAME LAST_NAME")
    for player in players:
        print(f"{player.UNIFORM_NUM} {player.FIRST_NAME} {player.LAST_NAME}")
def query5(session, num_wins):
    # Join the Player and Team tables on the TEAM_ID foreign key
    results = session.query(PLAYER.FIRST_NAME,
                                  PLAYER.LAST_NAME,
                                  TEAM.NAME,
                                  TEAM.WINS)\
                          .join(TEAM)\
                          .filter(TEAM.WINS > num_wins)
    print("FIRST_NAME LAST_NAME TEAM_NAME WINS")
    for player_team  in results:
        print(f"{player_team .FIRST_NAME} {player_team .LAST_NAME} {player_team .NAME} {player_team .WINS}")
if __name__ == '__main__':
    query1(session, 1, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    query2(session, "Orange")
    query3(session, "Duke")
    query4(session, "NC", "LightBlue")
    query5(session, 6)    

