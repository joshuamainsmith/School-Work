-- Name where generic > brand
SELECT Product.Proprietary_name
FROM Product, Pharmacy
WHERE Product.productID = pharmacy.ndc AND Pharmacy.Classification = 'B' AND Pharmacy.NADAC_Per_Unit < Pharmacy.Generic.Price;

-- Name where generic < brand
SELECT Product.Proprietary_name
FROM Product, Pharmacy
WHERE Product.productID = pharmacy.ndc AND Pharmacy.Classification = 'B' AND Pharmacy.NADAC_Per_Unit > Pharmacy.Generic.Price;

-- Pharmacy drug that's a brand name and OTC, but cheaper than its generic equivalent
SELECT Product.Proprietary_name
FROM Product, Pharmacy
WHERE Product.productID = pharmacy.ndc 
    AND Pharmacy.Classification = 'B' 
    AND Pharmacy.OTC = 'Y' 
    AND Pharmacy.NADAC_Per_Unit < Pharmacy.Generic.Price;

-- Pharmacy drug that's a brand name and no t OTC, but cheaper than its generic equivalent
SELECT Product.Proprietary_name
FROM Product, Pharmacy
WHERE Product.productID = pharmacy.ndc
    AND Pharmacy.Classification = 'B' 
    AND Pharmacy.OTC = 'N' 
    AND Pharmacy.NADAC_Per_Unit < Pharmacy.Generic.Price;



-- Descending

-- Top 5 Most expensive drugs of any kind
Select Product.Proprietary_name, Pharmacy.NADAC_per_unit
From Product, Pharmacy
Where Product.productID = pharmacy.ndc
Group By Product.Proprietary_name
Order By Pharmacy.NADAC_per_unit DESC
Where rownum < 6;

-- Top 5 Most expensive Brand name druge
Select Product.Proprietary_name, Pharmacy.NADAC_per_unit
From Product, Pharmacy
Where Product.productID = pharmacy.ndc 
    AND Pharmacy.Classification = 'B'
Group By Product.Proprietary_name
Order By Pharmacy.NADAC_per_unit DESC
Where rownum < 6;

-- Top 5 Most expensive Generic name druge
Select Product.Proprietary_name, Pharmacy.NADAC_per_unit
From Product, Pharmacy
Where Product.productID = pharmacy.ndc 
    AND Pharmacy.Classification = 'G'
Group By Product.Proprietary_name
Order By Pharmacy.NADAC_per_unit DESC
Where rownum < 6;

-- Top 5 Most expensive Brand name druge and cost of generic equivalent
Select Product.Proprietary_name, Pharmacy.NADAC_per_unit, Pharmacy.Generic_Price
From Product, Pharmacy
Where Product.productID = pharmacy.ndc 
    AND Pharmacy.Classification = 'B'
Group By Product.Proprietary_name
Order By Pharmacy.NADAC_per_unit DESC
Where rownum < 6;

-- Ascending

-- Top 5 Least expensive drugs of any kind
Select Product.Proprietary_name, Pharmacy.NADAC_per_unit
From Product, Pharmacy
Where Product.productID = pharmacy.ndc
Group By Product.Proprietary_name
Order By Pharmacy.NADAC_per_unit ASC
Where rownum < 6;

-- Top 5 Least expensive Brand name druge
Select Product.Proprietary_name, Pharmacy.NADAC_per_unit
From Product, Pharmacy
Where Product.productID = pharmacy.ndc 
    AND Pharmacy.Classification = 'B'
Group By Product.Proprietary_name
Order By Pharmacy.NADAC_per_unit ASC
Where rownum < 6;

-- Top 5 Least expensive Generic name druge
Select Product.Proprietary_name, Pharmacy.NADAC_per_unit
From Product, Pharmacy
Where Product.productID = pharmacy.ndc 
    AND Pharmacy.Classification = 'G'
Group By Product.Proprietary_name
Order By Pharmacy.NADAC_per_unit ASC
Where rownum < 6;

-- Top 5 Least expensive Brand name druge and cost of generic equivalent
Select Product.Proprietary_name, Pharmacy.NADAC_per_unit, Pharmacy.Generic_Price
From Product, Pharmacy
Where Product.productID = pharmacy.ndc 
    AND Pharmacy.Classification = 'B'
Group By Product.Proprietary_name
Order By Pharmacy.NADAC_per_unit ASC
Where rownum < 6;