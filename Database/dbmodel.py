from sqlalchemy import Column, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from pydantic import BaseModel

# SQLAlchemy setup
Base = declarative_base()

# Database model for Pokémon
class Pokemon(Base):
    __tablename__ = 'pokemon'
 # might need id to auto increment? making this true for now
    id = Column(Integer, primary_key=True, autoincrement=True)
    dex = Column(Integer)
    name = Column(String)
    imageurl = Column(String)
    maxHp = Column(Integer)
    currHp = Column(Integer)

    def __repr__(self):
        return f"<Pokemon(id={self.id}, pokedex_number={self.dex}, name='{self.name}', imageurl='{self.imageurl}', maxHp='{self.maxHp}', currHp='{self.currHp}')>"

class PokemonCreate(BaseModel):
    id: int
    dex: int
    name: str
    imageurl: str
    maxHp: int
    currHp: int

class PokemonRead(PokemonCreate):
    class Config:
        orm_mode = True
