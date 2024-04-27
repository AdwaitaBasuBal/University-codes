#MARKETING!

# question 2 : users with no photos
SELECT * 
FROM users 
WHERE users.id NOT IN 
      (SELECT users.id 
      FROM 
         users RIGHT JOIN photos 
         ON users.id = photos.user_id) ;

# question 3 : winner of maximum likes
# way 1:
CREATE VIEW Contest_winner AS 
	(WITH Winner_table AS 
	     (SELECT photos.user_id, photos.image_url, photos.created_dat, photos.id, (COUNT(likes.photo_id)) AS total_likes 
          FROM 
			likes INNER JOIN photos 
            ON likes.photo_id = photos.id 
		 GROUP BY likes.photo_id 
         ORDER BY total_likes DESC)
	SELECT * 
    FROM Winner_table 
	WHERE total_likes IN 
	    (SELECT max(total_likes) AS winner 
         FROM Winner_table));

SELECT * 
FROM 
   users INNER JOIN Contest_winner
   ON users.id = Contest_winner.user_id;

# way 3:
CREATE VIEW Contest_win AS (SELECT photos.user_id, photos.image_url, photos.created_dat, photos.id, (count(likes.photo_id)) AS total_likes 
FROM 
    likes INNER JOIN photos 
    ON likes.photo_id = photos.id 
GROUP BY likes.photo_id 
ORDER BY total_likes DESC 
LIMIT 1);

SELECT * 
FROM 
   users INNER JOIN Contest_win
   ON users.id = Contest_win.user_id;

# question 5 : maximum register day of the week

#question 1 :  Find the 5 oldest users of the Instagram from the database provided
SELECT *
FROM users
ORDER BY created_at ASC
LIMIT 5;

# question 4 : top 5 most commonly used hashtags on the platform
SELECT tags.id, tags.tag_name, (count(photo_tags.tag_id)) AS tag_popularity 
FROM 
    photo_tags INNER JOIN tags 
    ON photo_tags.tag_id = tags.id 
GROUP BY photo_tags.tag_id 
ORDER BY tag_popularity DESC 
LIMIT 5;

#INVESTOR METRICES

#question 2 : Find the fake bots
WITH Liked_photos 
    AS (SELECT user_id, count(photo_id) 
        AS total_photos 
        FROM likes 
        GROUP BY(user_id))
SELECT * 
FROM 
    users INNER JOIN Liked_photos 
    ON users.id = Liked_photos.user_id 
WHERE total_photos IN 
	(SELECT max(total_photos) 
    FROM Liked_photos);
    
    CREATE VIEW user_count AS(select count(id) AS total_users FROM users);
    SELECT sum(Total_table.total_photos_of_each)/user_count.total_users AS photos_by_user, avg(Total_table.total_photos_of_each) AS average_postsperuser 
    FROM 
        (SELECT user_id, count(id), 
        AS total_photos_of_each 
        FROM photos
        GROUP BY(user_id))
        Total_table INNER JOIN user_count 
        ON total_table.user_id = user_count.id;

#PROJECT 3 CASE STUDY : 1

#question 1: jobs per hour per day
SELECT 
    ds, COUNT(job_id)AS jobs_reviewed, (SUM(time_spent)/3600) AS hours
FROM 
    job_data 
WHERE 
    ds LIKE '%-11-%' 
GROUP BY 
    ds
ORDER BY 
    ds;

#question 4: Duplicate rows
WITH duplicate_rows AS 
    (SELECT 
        *, ROW_NUMBER() OVER(PARTITION BY ds, job_id, actor_id, `event`, `language`, time_spent, org) AS checking
    FROM 
        job_data)
SELECT 
    * 
FROM 
    duplicate_rows 
WHERE 
    checking > 1;

#question 3: percentage per language
SELECT 
    `language`, ((COUNT(`language`) / total_language) * 100) AS percentage
FROM 
    job_data
CROSS JOIN (
    SELECT 
        COUNT(`language`) AS total_language
    FROM 
        job_data
    WHERE 
        ds BETWEEN 
            (SELECT 
                DATE_SUB(MAX(ds), INTERVAL 30 DAY) 
			FROM 
                job_data) 
		AND 
			(SELECT MAX(ds) FROM job_data)
) AS SUM_table
WHERE 
    ds BETWEEN 
        (SELECT 
            DATE_SUB(MAX(ds), INTERVAL 30 DAY) 
        FROM job_data)
	AND 
        (SELECT MAX(ds) FROM job_data)
GROUP BY 
    `language`, total_language;

#question 2: 7 day rolling
WITH throughput__table AS 
    (SELECT 
        ds, COUNT(*) AS throughput
	 FROM
        job_data
     WHERE
        ds LIKE '%-11-%'
     GROUP BY
        ds)
SELECT 
    ds, AVG(throughput) OVER (ORDER BY ds ROWS BETWEEN 6 PRECEDING AND CURRENT ROW) AS 7day_rolling_average
FROM 
    throughput__table
ORDER BY
    ds;
#PROJECT 3 CASE STUDY: 2

#question 1: Weekly user engagement
CREATE VIEW Weekly_user_engagement AS 
    (SELECT 
        YEAR(occured_at) as `year`, MONTHNAME(occured_at) as `month`, WEEK(occured_at) AS `week`, COUNT(DISTINCT user_id) AS active_users
    FROM 
        `events`
	WHERE 
        event_type = 'engagement'
    GROUP BY 
        `year`, `month`, `week`
    ORDER BY 
        `month` desc);

SELECT * 
FROM 
    Weekly_user_engagement;
#question 2: User growth over time

SELECT 
    YEAR(occured_at) as `year`, MONTHNAME(occured_at) as `month`, WEEK(occured_at) AS `week`,
	COUNT(DISTINCT user_id) AS total_users,
	(COUNT(DISTINCT user_id) - LAG(COUNT(DISTINCT user_id)) OVER(ORDER BY WEEK(occured_at))) / 
	    LAG(COUNT(DISTINCT user_id)) OVER (ORDER BY WEEK(occured_at))*
        100 AS user_growth_rate,
	(SUM(COUNT(DISTINCT user_id)) OVER(ORDER BY WEEK(occured_at) ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW)) AS user_growth_number
FROM 
    `events`
GROUP BY 
	`year`,`week`, `month`
ORDER BY 
   `year`,`week`, `month`;
    
#question 3: Weekly retention
#Retention rate = (# Users on day 7 / # Users on day 1) * 100
with retention_table AS 
    (SELECT 
        *, (active_users/LAG(active_users) OVER ()) * 100 as retention_rate
    FROM Weekly_user_engagement)

SELECT * FROM retention_table;

WITH sign_up_cohort AS (
    SELECT
        user_id,
        MIN(occured_at) AS sign_up_week
    FROM `events`
    WHERE event_type = 'signup_flow'
    GROUP BY user_id
),
weekly_retention AS (
    SELECT
        sc.sign_up_week,
        WEEK(e.occured_at) AS retention_week,
        COUNT(DISTINCT e.user_id) AS active_users
    FROM
        sign_up_cohort sc
        JOIN `events` e ON sc.user_id = e.user_id
    WHERE
        WEEK(e.occured_at) > WEEK(sc.sign_up_week) -- Exclude the sign-up week itself
    GROUP BY
        sc.sign_up_week, retention_week
)
SELECT
    sign_up_week,
    retention_week,
    active_users,
    (active_users / (SELECT COUNT(DISTINCT user_id) FROM sign_up_cohort WHERE WEEK(sign_up_week) = WEEK(sign_up_cohort.sign_up_week))) * 100 AS retention_rate
FROM
    weekly_retention
ORDER BY
    sign_up_week, retention_week;

#question D
SELECT 
        Device, YEAR(occured_at) as `year`, MONTHNAME(occured_at) as `month`, WEEK(occured_at) AS `week`, COUNT(DISTINCT user_id) AS active_users
    FROM 
        `events`
	WHERE 
        event_type = 'engagement'
    GROUP BY 
        Device, `year`, `month`, `week`
    ORDER BY 
        Device, `year`, `month` desc;
        
        
#question E
SELECT 
        `action` AS email_type, YEAR(occured_at) as `year`, MONTHNAME(occured_at) as `month`, WEEK(occured_at) AS `week`, COUNT(DISTINCT user_id) AS users_of_email_services
    FROM 
        `email_events`
    GROUP BY 
        `action`, `year`, `month`, `week`
    ORDER BY 
        `action`, `year`, `month` desc;
        
