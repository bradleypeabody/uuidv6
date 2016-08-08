
import uuid

myu1 = uuid.uuid1()

def uuidv1tov6(u):
	uh = u.hex
	tlo1 = uh[:5]
	tlo2 = uh[5:8]
	tmid = uh[8:12]
	thig = uh[13:16]
	rest = uh[16:]
	uh6 = thig + tmid + tlo1 + '6' + tlo2 + rest
	return uuid.UUID(hex=uh6)


myu6 = uuidv1tov6(myu1)

print (myu1)
print (myu6)

# 01234567890123456789012345678901
# e6a0fcc25d8c11e69774c8bcc8a0b17d