from sqlalchemy import create_engine

# Define the database URL
db_url = f'postgresql://postgres:passw0rd@localhost:5432/ACC_BBALL'

# Create an engine object
engine = create_engine(db_url)

# Define a SQL query
query = "SELECT * FROM PLAYER"

# Execute the query and retrieve the results as a list of dictionaries
with engine.connect() as connection:
    result = connection.execute(query).fetchall()
    rows = [dict(row) for row in result]

# Print the rows
print(rows)