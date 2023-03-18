from sqlalchemy import Column, Integer, String, Float, ForeignKey, create_engine
from sqlalchemy.orm import relationship, declarative_base, sessionmaker
#from sqlalchemy.ext.declarative import declarative_base

# Define the database URL
# change a database
db_url = f'postgresql://postgres:passw0rd@localhost:5432/ACC_BBALL_py'

# Create an engine object
engine = create_engine(db_url)
#Session = sessionmaker(bind=engine)

Base = declarative_base()

class STATE(Base):
    __tablename__ = 'STATE'

    STATE_ID = Column(Integer, primary_key=True, nullable=False)
    NAME = Column(String(50), nullable=False)

class COLOR(Base):
    __tablename__ = 'COLOR'

    COLOR_ID = Column(Integer, primary_key=True, nullable=False)
    NAME = Column(String(50), nullable=False)

class TEAM(Base):
    __tablename__ = 'TEAM'

    TEAM_ID = Column(Integer, primary_key=True, nullable=False)
    NAME = Column(String(50), nullable=False)
    STATE_ID = Column(Integer, ForeignKey('STATE.STATE_ID'), nullable=False)
    COLOR_ID = Column(Integer, ForeignKey('COLOR.COLOR_ID'), nullable=False)
    WINS = Column(Integer, nullable=False)
    LOSSES = Column(Integer, nullable=False)
    #The backref argument specifies a name for the reverse relationship, which allows you to access the related objects from the other side of the relationship.
    #relationship() function, which creates a one-to-many relationship between the two tables
    state = relationship("STATE", backref="teams")
    color = relationship("COLOR", backref="teams")

class PLAYER(Base):
    __tablename__ = 'PLAYER'

    PLAYER_ID = Column(Integer, primary_key=True, nullable=False)
    TEAM_ID = Column(Integer, ForeignKey('TEAM.TEAM_ID'), nullable=False)
    UNIFORM_NUM = Column(Integer, nullable=False)
    FIRST_NAME = Column(String(50), nullable=False)
    LAST_NAME = Column(String(50), nullable=False)
    MPG = Column(Integer, nullable=False)
    PPG = Column(Integer, nullable=False)
    RPG = Column(Integer, nullable=False)
    APG = Column(Integer, nullable=False)
    SPG = Column(Float(4,1), nullable=False)
    BPG = Column(Float(4,1), nullable=False)

    team = relationship("TEAM", backref="players")
# Drop the tables if they exist
Base.metadata.drop_all(engine)
# When define a model class like STATE or PLAYER and inherit from Base, the class definition sets up the corresponding Table object in the metadata
Base.metadata.create_all(engine)

"""
# Load data into the State table
with open("state.txt") as f:
    for line in f:
        state_id, name = line.strip().split()
        state = STATE(state_id=state_id, name=name)
        session.add(state)

# Load data into the Color table
with open("color.txt") as f:
    for line in f:
        color_id, name = line.strip().split()
        color = Color(color_id=color_id, name=name)
        session.add(color)

# Load data into the Team table
with open("team.txt") as f:
    for line in f:
        team_id, name, state_id, color_id, wins, losses = line.strip().split()
        team = COLOR(team_id=team_id, name=name, state_id=state_id, color_id=color_id, wins=wins, losses=losses)
        session.add(team)

# Load data into the Player table
with open("player.txt") as f:
    for line in f:
        player_id, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg = line.strip().split()
        player = Player(player_id=player_id, team_id=team_id, uniform_num=uniform_num, first_name=first_name, last_name=last_name, mpg=mpg, ppg=ppg, rpg=rpg, apg=apg, spg=spg, bpg=bpg)
        session.add(player)

# Commit changes to the database
session.commit()
"""