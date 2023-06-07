--Assignment: Make your own ques which have the usage of variables and if\when statement
-- Question: Find how many students are curretnly enrolled and check if we can add more students or not?
SET VERIFY OFF
SET SERVEROUTPUT ON;
DECLARE
    total_seat NUMBER;
    total_student NUMBER;
BEGIN

    -- Get user input
    total_seat := &input;

    -- Query to count rows in the STUDENT table
    SELECT COUNT(*) INTO total_student FROM STUDENT;

    -- Compare the row count with user input
    IF total_student > total_seat THEN
        DBMS_OUTPUT.PUT_LINE('There are more students than seats.');
    ELSIF total_student < total_seat THEN
        DBMS_OUTPUT.PUT_LINE('There are less students than seats.');
	ELSE
		DBMS_OUTPUT.PUT_LINE('There are exactly eual student as seat.');
    END IF;
END;
/