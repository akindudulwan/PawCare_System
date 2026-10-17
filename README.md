# PawCare - Pet Care System

PawCare is an Object-Oriented Pet Care and Clinic Management System implemented in Visual Studio C++/CLI (.NET Framework) with MySQL / MariaDB database integration.

## Project Structure
- `Forms/`: Windows Forms GUI (Login, Dashboard, Owner, Pet, Appointment, Billing, Medical Records, Vet and Reception Portals).
- `Models/`: Core OOP Entities (`Pet`, `Dog`, `Cat`, `Owner`, `Veterinarian`, `Appointment`, `MedicalRecord`, `Payment`).
- `Database/`: ADO.NET MySQL Database Manager (`DatabaseManager.h`/`.cpp`) and schema script (`pawcare_db.sql`).
- `packages/`: MySQL Connector/NET libraries and dependencies.

## How to Run in Visual Studio
1. Open `PawCare.sln` in **Visual Studio 2022** (or later).
2. Ensure C++/CLI support for v143 build tools is installed.
3. Set configuration to `Debug` and platform to `x64`.
4. Build Solution (`Ctrl + Shift + B`).
5. Run the application (`F5`).

## Database Setup & Credentials
1. Import `Database/pawcare_db.sql` into MySQL / MariaDB using phpMyAdmin, HeidiSQL, or MySQL Workbench:
```sql
source Database/pawcare_db.sql;
```

2. Configured Connection Settings:
- **Server / Host**: `localhost` (port 3306)
- **Database Name**: `pawcare_db`
- **Username**: `root`
- **Password**: `2004`

