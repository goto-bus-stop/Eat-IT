<?php
/*
 * Authors: Marijn Pool & René Kooi
 */


class View {

    public function displayAll(Collection $models){
        $content ="<table>";
        $models->load();
        $model = $models->first();

        $content .= "<tr>";
        foreach($model::getSchema() as $fieldname => $type){
           $content .= "<th>".$fieldname."</th>";
        }
        $content .= "<th>Action</th></tr>";
        foreach($models as $child) {
            $content .= "<tr>";
            foreach($child->toArray() as $key=>$value){
                $content .= "<td>" . $value . "</td>";
            }
            $id = $child->id;
            $type = get_class($child);
            $content .= "<td><a href=\"index.php?q=/$type/edit/$id\">Edit</a>";
            $content .= "|<a class=\"delete\" href=\"javascript:confirmAction('Are you sure?', 'index.php?q=/$type/remove/$id');\">Remove</a>";
            $content .= "</tr>";
        }
        $content .= "</table>";
        return $content;
     //   print_r($model::all());
    }


    public function displayAdd($model){
        return $this->addForm($model);
    }


    private function addForm($model){
        $type = get_class($model);
        $form = "<form method=\"post\" action=\"index.php?q=/$type/insert\">";
        $form .= "<table>\n";
        foreach($model::getSchema() as $fieldname => $type){
            $form .= "  <tr>\n";
            $form .= "      <td>".$fieldname."</td><td>".$this->inputFieldCreator($fieldname,$type,NULL)."</td>\n";
        }
        $form .="<tr><td></td><td><input type=\"submit\" value=\"Save\" /></td></tr>\n";
        $form .="</table>\n";
        $form .="</form>\n";
        return $form;

    }




    /**
     * @param $model
     */
    public function displayEdit(Model $model){
        return $this->editForm($model);
    }

    private function editForm(Model $model){
        $type = get_class($model);
        $id = $model->id;
        $form = "<form method=\"post\" action=\"index.php?q=/$type/save/$id\">";
        $form .= "<table>\n";
        $data = $model->toArray();    
        foreach($model::getSchema() as $fieldname => $type){
            $form .= "  <tr>\n";
            $form .= "      <td>".$fieldname."</td><td>".$this->inputFieldCreator($fieldname,$type,$data[$fieldname])."</td>\n";
        }
        $form .="<tr><td></td><td><input type=\"submit\" value=\"Save\" /></td></tr>\n";
        $form .="</table>\n";
        $form .="</form>\n";
        return $form;

    }

    protected function inputFieldCreator($fieldname,$type,$data){
        switch($type['type']){
            case "id":
                return "<input type='text' maxlength='4' name='$fieldname' value='$data'     />";
            case "string":
                return "<input type='text' maxlength='".$type['param']."' name='$fieldname' value='$data' />";
            case "double":
                return "<input type='text' name='$fieldname' value='$data'  />";
            case "int":
                return "<input type='text' name='$fieldname' value='$data'  />";
            case "date":
                return "<input type='text' name='$fieldname' id='datefield' value='$data'  />";
            case "link":
                return $this->createDropdown($type['param'], $fieldname);//var_dump($var::all());
            default:
                return "NOT IMPLEMENTED";

        }
    }

    protected function createDropdown($model, $fieldname){
        $select = "    <select name='$fieldname'>\n";
        foreach ($model::all() as $child) {
            $primaryKey =  $child->{$child::getSchema()->getPrimaryKey()};
            $select .= "        <option value='$primaryKey'>$child</option>\n";
        }
        $select .="    </select>\n";
        return $select;
    }


}