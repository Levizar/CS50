-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Goals:
-- Who the thief is,
-- What city the thief escaped to, and
-- Who the thief’s accomplice is who helped them escape


-- get all the tables
.tables
-- airports                  crime_scene_reports       people
-- atm_transactions          flights                   phone_calls
-- bank_accounts             interviews
-- courthouse_security_logs  passengers

-- get the table columns
.schema crime_scene_reports

-- get crime scene reports for the date it happens
SELECT * FROM crime_scene_reports WHERE year = 2020 and month = 7 and day = 28;

-- get only the cs50 report
SELECT * FROM crime_scene_reports WHERE id = 295;
-- results: Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time each of their interview transcripts mentions the courthouse.

.schema interviews

-- get witness name and transcript of interviews happening that day and containing courthouse
SELECT name, transcript FROM interviews WHERE year = 2020 and month = 7 and day = 28 and transcript like '%courthouse%';
-- Ruth : in the next 10 min, thief went away with his car
-- -> check all plate for car leaving at that time
-- Eugene: He saw the thief using the ATM to withdraw on Fifer Street in the morning before he arrived at the courthouse
-- Check ATM of Fifer street for that day
-- Raymond: He eared the thief calling someone: thief ask someone to buy plane ticket for the next morning
-- check phone calls and plane tickets

-- get witness informations
SELECT * from people where name in (SELECT name FROM interviews WHERE year = 2020 and month = 7 and day = 28 and transcript like '%courthouse%');

-- get all license_plate, and people related to it, leaving the courthouse in the next 10 min of the crime
SELECT * FROM courthouse_security_logs csl
INNER JOIN people p on csl.license_plate = p.license_plate
WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity like 'exit';
-- 8 vehicules

-- get Eugene time of arrival
SELECT license_plate from people where name like 'Eugene';
SELECT * FROM courthouse_security_logs csl
WHERE year = 2020 and month = 7 and day = 28 and activity like 'entrance' and license_plate like '47592FJ';
-- It seems that Eugene never came by car :/
--> check atm transaction before 12 on fifer street

-- get people using this atm that day
SELECT *  FROM atm_transactions at
INNER JOIN bank_accounts ba on at.account_number = ba.account_number
INNER JOIN people p on ba.person_id = p.id
WHERE at.atm_location like 'fifer street' and at.year = 2020 and at.month = 7 and at.transaction_type like 'withdraw';

-- get people + infos using this atm that day and exiting the courthouse
SELECT *  FROM atm_transactions at
INNER JOIN bank_accounts ba on at.account_number = ba.account_number
INNER JOIN people p on ba.person_id = p.id
INNER JOIN courthouse_security_logs csl on csl.license_plate = p.license_plate
WHERE at.atm_location like 'fifer street' and at.year = 2020 and at.month = 7 and at.day = 28 and at.transaction_type like 'withdraw' and
csl.year = 2020 and csl.month = 7 and csl.day = 28 and csl.hour = 10 and csl.minute >= 15 and csl.minute <= 25 and csl.activity like 'exit';

-- The thief called someone during the day and took the plane the next day

-- get all the tables
.tables
-- X airports                  X crime_scene_reports     X people
-- X atm_transactions          X flights                   Xphone_calls
-- X bank_accounts             X interviews
-- X courthouse_security_logs  X passengers

SELECT * FROM flights f
INNER JOIN passengers pas on f.id = pas.flight_id
INNER JOIN people p on p.passport_number = pas.passport_number
WHERE f.origin_airport_id in (SELECT id FROM airports a WHERE a.city like 'fiftyville')
and f.year = 2020 and f.month = 7 and f.day = 29;


-- only query the info of the thief
SELECT * from people where name in (
    -- get the name of people leaving in the 10 min and using the atm and calling someone that day and having an airport ticket the next day
    SELECT DISTINCT name FROM atm_transactions at
    INNER JOIN bank_accounts ba ON at.account_number = ba.account_number
    INNER JOIN people p ON ba.person_id = p.id
    INNER JOIN courthouse_security_logs csl ON csl.license_plate = p.license_plate
    INNER JOIN phone_calls pc ON pc.caller like p.phone_number
    WHERE
    -- used the atm that day
    at.atm_location LIKE 'fifer street' AND at.year = 2020 AND at.month = 7 AND at.day = 28 AND at.transaction_type LIKE 'withdraw' AND
    -- exited in the 10 next min
    csl.year = 2020 AND csl.month = 7 AND csl.day = 28 AND csl.hour = 10 AND csl.minute >= 15 AND csl.minute <= 25 AND csl.activity LIKE 'exit' AND
    -- called someone that day
    pc.year = 2020 AND pc.month = 7 AND pc.day = 28
    -- has a passenger ticket to leave the city next day in the morning
    AND p.passport_number in (
        SELECT pas.passport_number FROM flights f
        INNER JOIN passengers pas on f.id = pas.flight_id
        WHERE f.origin_airport_id in (SELECT id FROM airports a WHERE a.city like 'fiftyville')
        and f.year = 2020 and f.month = 7 and f.day = 29 and f.hour < 12
    )
);

-- query the thief's phone call
SELECT * FROM phone_calls pc
WHERE pc.caller LIKE '(367) 555-5533' AND pc.year = 2020 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60;

-- Query the thief's flight
SELECT * FROM flights f
INNER JOIN passengers pas on f.id = pas.flight_id
INNER JOIN airports a1 on f.origin_airport_id = a1.id
INNER JOIN airports a2 on f.destination_airport_id = a2.id
WHERE a1.city like 'fiftyville'
and f.year = 2020 and f.month = 7 and f.day = 29 and f.hour < 12
and pas.passport_number = 5773159633;

SELECT * FROM people p
where p.phone_number in (
    -- query the thief's phone call
    SELECT pc.receiver FROM phone_calls pc
    WHERE pc.caller LIKE '(367) 555-5533' AND pc.year = 2020 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60
);