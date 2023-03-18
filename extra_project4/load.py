from sqlalchemy.orm import sessionmaker
from model import engine, STATE, COLOR, TEAM, PLAYER

# Create a session object
Session = sessionmaker(bind=engine)
session = Session()

def clearTables():
    session.query(STATE).delete()
    session.query(COLOR).delete()
    session.query(TEAM).delete()
    session.query(PLAYER).delete()
    session.commit()

def loadStateTable():
    with open('state.txt') as infile:
        for line in infile:
            stateId, name = line.strip().split()
            state = STATE(STATE_ID=stateId, NAME=name)
            session.add(state)
    
    session.commit()

def loadColorTable():
    with open('color.txt') as infile:
        for line in infile:
            colorId, name = line.strip().split()
            color = COLOR(COLOR_ID=colorId, NAME=name)
            session.add(color)
    session.commit()

def loadTeamTable():
    with open('team.txt') as infile:
        for line in infile:
            teamId, name, stateId, colorId, wins, losses = line.strip().split()
            team = TEAM(TEAM_ID=teamId, NAME=name, STATE_ID=stateId, COLOR_ID=colorId, WINS=wins, LOSSES=losses)
            session.add(team)
    session.commit()

def loadPlayerTable():
    with open('player.txt') as infile:
        for line in infile:
            playerId, teamId, uniformNum, firstName, lastName, mpg, ppg, rpg, apg, spg, bpg = line.strip().split()
            player = PLAYER(
                PLAYER_ID=playerId, TEAM_ID=teamId, UNIFORM_NUM=uniformNum, FIRST_NAME=firstName,
                LAST_NAME=lastName, MPG=mpg, PPG=ppg, RPG=rpg, APG=apg, SPG=spg, BPG=bpg
            )
            session.add(player)
    session.commit()

def loadTables():
    loadStateTable()
    loadColorTable()
    loadTeamTable()
    loadPlayerTable()

clearTables()
loadTables()
if __name__ == '__main__':
    clearTables()
    loadTables()
