from pymongo import MongoClient


client = MongoClient("mongodb://localhost:27017/")
db = client['project3']  

def state_report():
    
    query = [
        {
            "$group": {
                "_id": "$state",
                "venue_count": {"$sum": 1}
            }
        },
        {"$sort": {"_id": 1}}
    ]
    print("\n     State Report:\n")
    results = db.venues.aggregate(query)
    for result in results:
        print(f"State of {result['_id']} has {result['venue_count']} Venues")

def artist_search():
    
    artist_name = input("\nNote: Input is Case Sensitive and Space Sensitive.\nEnter the artist's name: ").strip()
    print("\n     Artist Concerts:\n")
    concerts = db.concerts.find({"performers.artist.name": artist_name}, {
        "title": 1,
        "start": 1,
        "venue.name": 1,
        "venue.city": 1,
        "venue.state": 1,
        "_id": 0
    })
    for concert in concerts:
        print(f"Title: {concert['title']} Timestamp: {concert['start']} Location: {concert['venue']['name']}, "
              f"{concert['venue']['city']}, {concert['venue']['state']}")


def general_admission_totals():
   
    query = [
        {
            "$match": {"state": "CA"}
        },
        {
            "$unwind": "$sections"
        },
        {
            "$match": {"sections.title": "General Admission"}
        },
        {
            "$lookup": {
                "from": "tickets",
                "localField": "sections.title",         
                "foreignField": "seat.sectionTitle",     
                "as": "general_admission_tickets"
            }
        },
        {
            "$unwind": "$general_admission_tickets"
        },
        {
            "$group": {
                "_id": {
                    "venue_name": "$name",
                    "section_title": "$sections.title"
                },
                "total_price": {"$sum": "$general_admission_tickets.price"}  
            }
        },
        {
            "$sort": {"_id.venue_name": 1}
        }
    ]

    
    print("\n     General Admission Totals:\n")
    results = db.venues.aggregate(query)
    found = False

    for result in results:
        found = True
        venue_name = result['_id']['venue_name']
        section_title = result['_id']['section_title']
        total_price = result['total_price']
        print(f"{venue_name} - {section_title} - ${total_price}")
    
    if not found:
        print("Error: No Totals")




def main_menu():
    while True:
        print("\nMUSTARDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD")
        print("1. State report")
        print("2. Artist search")
        print("3. General admission totals")
        print("4. Exit")
        
        choice = input("Enter your choice: ").strip()
        if choice == "1":
            state_report()
        elif choice == "2":
            artist_search()
        elif choice == "3":
            general_admission_totals()
        elif choice == "4":
            print("\nExiting")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main_menu()
