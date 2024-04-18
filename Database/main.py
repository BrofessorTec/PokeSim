from fastapi import FastAPI, HTTPException, Depends
from fastapi.middleware.cors import CORSMiddleware
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, Session
from pydantic import BaseModel

# Imports from dbmodel.py file
from dbmodel import Base, Pokemon, PokemonCreate, PokemonRead

app = FastAPI()

# enable CORS to make requests to the FastAPI server
app.add_middleware(
	CORSMiddleware,
	allow_origins=["*"], 
	allow_credentials=True,
	allow_methods=["*"],
	allow_headers=["*"],
)

# Set up the local database session
# using the inventory as the main db for now.. might hard code the possible poke's rather than 2 db at once
SQLALCHEMY_DATABASE_URL = "sqlite:///./inventory.db"
engine = create_engine(SQLALCHEMY_DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

# This binds the ORM class models
Base.metadata.create_all(bind=engine)

# This function will serve as a Dependency Inversion for our db connection at our FastAPI endpoints.
# Each endpoint function will have this connection passed in as a parameter using the Depends() function.
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
      
# GET requests
@app.get("/count")
async def get_count(db: Session = Depends(get_db)):
    return db.query(Pokemon).count()

@app.get("/pokemon")
async def get_pokemon(db: Session = Depends(get_db)):
    pokemon_list = db.query(Pokemon).all()

    return [{"id": pokemon.id, "dex": pokemon.dex, "name": pokemon.name, "imageurl": pokemon.imageurl, "maxHp": pokemon.maxHp, "currHp": pokemon.currHp} for pokemon in pokemon_list]

@app.get("/pokemon/{id}")
async def get_pokemon_by_id(id: int, db: Session = Depends(get_db)):
    pokemon = db.query(Pokemon).filter(Pokemon.id == id).first()

    if pokemon is None:
        raise HTTPException(status_code=404, detail="Pokemon not found")

    return pokemon

# POST request
@app.post("/pokemon")
async def add_pokemon(pokemon: PokemonCreate, db: Session = Depends(get_db)):
    # Check if the pokemon already exists in the database
    if db.query(Pokemon).filter(Pokemon.id == pokemon.id).first() is not None:
        raise HTTPException(status_code=400, detail="Pokemon already exists")

    # Create a new Pokemon object using the PokemonCreate model
    new_pokemon = Pokemon(id=pokemon.id, dex=pokemon.dex, name=pokemon.name, imageurl=pokemon.imageurl, maxHp=pokemon.maxHp, currHp=pokemon.currHp)

    # Add the new Pokemon object to the database
    db.add(new_pokemon)
    db.commit()
    db.refresh(new_pokemon)

    # Return the new Pokemon object using the PokemonRead model
    return new_pokemon

# PUT request
@app.put("/pokemon/{id}")
async def update_pokemon(id: int, pokemon: PokemonCreate, db: Session = Depends(get_db)):
    # Check if the pokemon already exists in the database
    if db.query(Pokemon).filter(Pokemon.id == id).first() is None:
        raise HTTPException(status_code=404, detail="Pokemon not found")

    # Update the Pokemon object in the database
    db.query(Pokemon).filter(Pokemon.id == id).update({Pokemon.dex: pokemon.dex, Pokemon.name: pokemon.name, Pokemon.imageurl: pokemon.imageurl, Pokemon.maxHp: pokemon.maxHp, Pokemon.currHp: pokemon.currHp})
    db.commit()

    # Return the updated Pokemon object using the PokemonRead model
    return db.query(Pokemon).filter(Pokemon.id == id).first()

# PATCH requests
@app.patch("/pokemon/{id}/dex")
async def update_pokemon_name(id: int, dex: int, db: Session = Depends(get_db)):
    # Check if the pokemon already exists in the database
    if db.query(Pokemon).filter(Pokemon.id == id).first() is None:
        raise HTTPException(status_code=404, detail="Pokemon not found")

    # Update the Pokemon object in the database
    db.query(Pokemon).filter(Pokemon.id == id).update({Pokemon.dex: dex})
    db.commit()

    # Return the updated Pokemon object using the PokemonRead model
    return db.query(Pokemon).filter(Pokemon.id == id).first()

@app.patch("/pokemon/{id}/name")
async def update_pokemon_name(id: int, name: str, db: Session = Depends(get_db)):
    # Check if the pokemon already exists in the database
    if db.query(Pokemon).filter(Pokemon.id == id).first() is None:
        raise HTTPException(status_code=404, detail="Pokemon not found")

    # Update the Pokemon object in the database
    db.query(Pokemon).filter(Pokemon.id == id).update({Pokemon.name: name})
    db.commit()

    # Return the updated Pokemon object using the PokemonRead model
    return db.query(Pokemon).filter(Pokemon.id == id).first()

@app.patch("/pokemon/{id}/imageurl")
async def update_pokemon_imageurl(id: int, imageurl: str, db: Session = Depends(get_db)):
    # Check if the pokemon already exists in the database
    if db.query(Pokemon).filter(Pokemon.id == id).first() is None:
        raise HTTPException(status_code=404, detail="Pokemon not found")

    # Update the Pokemon object in the database
    db.query(Pokemon).filter(Pokemon.id == id).update({Pokemon.imageurl: imageurl})
    db.commit()

    # Return the updated Pokemon object using the PokemonRead model
    return db.query(Pokemon).filter(Pokemon.id == id).first()

# can add a new patch for maxHp for level ups if ever added
@app.patch("/pokemon/{id}/maxHp")
async def update_pokemon_imageurl(id: int, maxHp: int, db: Session = Depends(get_db)):
    # Check if the pokemon already exists in the database
    if db.query(Pokemon).filter(Pokemon.id == id).first() is None:
        raise HTTPException(status_code=404, detail="Pokemon not found")

    # Update the Pokemon object in the database
    db.query(Pokemon).filter(Pokemon.id == id).update({Pokemon.maxHp: maxHp})
    db.commit()

    # Return the updated Pokemon object using the PokemonRead model
    return db.query(Pokemon).filter(Pokemon.id == id).first()

# need a new patch for currHp
@app.patch("/pokemon/{id}/currHp")
async def update_pokemon_imageurl(id: int, currHp: int, db: Session = Depends(get_db)):
    # Check if the pokemon already exists in the database
    if db.query(Pokemon).filter(Pokemon.id == id).first() is None:
        raise HTTPException(status_code=404, detail="Pokemon not found")

    # Update the Pokemon object in the database
    db.query(Pokemon).filter(Pokemon.id == id).update({Pokemon.currHp: currHp})
    db.commit()

    # Return the updated Pokemon object using the PokemonRead model
    return db.query(Pokemon).filter(Pokemon.id == id).first()

# DELETE request
@app.delete("/pokemon/{id}")
async def delete_pokemon(id: int, db: Session = Depends(get_db)):
    # Check if the pokemon already exists in the database
    if db.query(Pokemon).filter(Pokemon.id == id).first() is None:
        raise HTTPException(status_code=404, detail="Pokemon not found")

    # Delete the Pokemon object from the database
    db.query(Pokemon).filter(Pokemon.id == id).delete()
    db.commit()

    # Return a success message
    return {"message": "Pokemon deleted"}