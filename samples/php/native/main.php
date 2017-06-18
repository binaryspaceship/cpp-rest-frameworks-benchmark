<?php

$values = [];

for ($i = 0; $i < 10000; ++$i)
{
    $values[] = [
      'id'   => 'item-'.$i,
      'name' => 'Hello World',
      'type' => 'application'
    ];
}

echo json_encode($values);
